#include "sootModel_SECT.h"

using namespace std;
using namespace soot;

////////////////////////////////////////////////////////////////////////////////
///
/// Constructor taking pointers to chemistry models as input.
/// User creates these pointers nominally by "new-ing" them.
///
/// @param nsoot_            \input number of soot sections
/// @param nucl_             \input pointer to nucleation model.
/// @param grow_             \input pointer to growth model.
/// @param oxid_             \input pointer to oxidation model.
/// @param coag_             \input pointer to coagulation model.
/// @param binGrowthFactor_  \input geometric growth factor = F --> m[0]*(F^0, F^1, F^2...)
/// @param cMin_             \input number of carbon atoms in the smallest bin
///
////////////////////////////////////////////////////////////////////////////////

sootModel_SECT::sootModel_SECT(size_t            nsoot_,
                               nucleationModel  *nucl_,
                               growthModel      *grow_,
                               oxidationModel   *oxid_,
                               coagulationModel *coag_,
                               double            binGrowthFactor_, 
                               int               cMin_) :
        sootModel(nsoot_, nucl_, grow_, oxid_, coag_), 
        binGrowthFactor(binGrowthFactor_) {

    if (nsoot_ < 2)
        throw runtime_error("SECT requires nsoot>1");

    set_mBins(cMin_);

    psdMechType = psdMech::SECT;

    if (nucl->mechType == nucleationMech::PAH)
        beta_DSi.resize(nsoot);
}

////////////////////////////////////////////////////////////////////////////////
///
/// Constructor taking enumerations names as input.
/// Chemistry pointers are created (new-ed) here based on those enumerations.
///
/// @param nsoot_ \input number of soot sections
/// @param Nmech  \input one of enum class nucleationMech in sootDefs.h
/// @param Gmech  \input one of enum class growthMech in sootDefs.h
/// @param Omech  \input one of enum class oxidationMech in sootDefs.h
/// @param Cmech  \input one of enum class coagulationMech in sootDefs.h
/// @param binGrowthFactor_  \input geometric growth factor = F --> m[0]*(F^0, F^1, F^2...)
/// @param cMin_             \input number of carbon atoms in the smallest bin
///
////////////////////////////////////////////////////////////////////////////////

sootModel_SECT::sootModel_SECT(size_t          nsoot_,
                               nucleationMech  Nmech,
                               growthMech      Gmech,
                               oxidationMech   Omech,
                               coagulationMech Cmech,
                               double          binGrowthFactor_,
                               int             cMin_) :
        sootModel(nsoot_, Nmech, Gmech, Omech, Cmech), 
        binGrowthFactor(binGrowthFactor_) {

    if (nsoot_ < 2)
        throw runtime_error("SECT requires nsoot>1");

    set_mBins(cMin_);

    psdMechType = psdMech::SECT;

    if (nucl->mechType == nucleationMech::PAH)
        beta_DSi.resize(nsoot);
}

////////////////////////////////////////////////////////////////////////////////
///
/// Set the sectional mass coordinate locations: mass per particle at each size location.
///
/// @param cMin_ \input smallest bin size.
///
////////////////////////////////////////////////////////////////////////////////

void sootModel_SECT::set_mBins(const int cMin_) {

    mBins.resize(nsoot);
    for (size_t k = 0; k < nsoot; k++)
        mBins[k] = cMin_ * pow(binGrowthFactor, k) * gasSpMW[(size_t)gasSp::C] / Na;
}

////////////////////////////////////////////////////////////////////////////////
///
/// Compute PAH condensation terms for SECT model.
/// Function split out from setSourceTerms so that it can be called in nucleationModel_PAH
/// for computing the pah dimer concentration.
///
/// Function only called if nucleationMech::PAH.
/// Function called by nucleationModel_PAH::getNucleationSootRate
///
/// @param state  \input gas and soot state, set by user.
/// @param mDimer \input dimer mass (kg)
/// @return pah/soot sollision rate per dimer. Call it I. I*mDimer*nDimer = Cnd1 (=) kg/m3*s
///
////////////////////////////////////////////////////////////////////////////////

double sootModel_SECT::pahSootCollisionRatePerDimer(const state &state, const double mDimer) {

    //---------- compute beta_DSi; used here and in subsequent PAH condensation in setSourceTerms

    size_t k;

    for(k=0; k<nsoot; k++)
        beta_DSi[k] = coag->getCoagulationSootRate(state, mDimer, mBins[k]);

    //---------- compute I_beta_DS

    double I_beta_DS = 0.0;
    double term1, term2;

    k = 0;                                                    // 1st bin: loss via growth into 2nd
    term1 = beta_DSi[k]*state.sootVar[k]/(mBins[k+1]-mBins[k]);
    I_beta_DS -= term1*mBins[0];

    for(k=1; k<nsoot-1; k++) {                                // interior bins: gain from k-1, lose to k+1
        term2 = beta_DSi[k]*state.sootVar[k]/(mBins[k+1]-mBins[k]);
        I_beta_DS += mBins[k] * (term1 - term2);
        term1 = term2;
    }

    k = nsoot-1;                                              // last bin: gain from 2nd to last + condensation inside
    term2 = beta_DSi[k]*state.sootVar[k]/mBins[k];
    I_beta_DS += mBins[k] * (term1 + term2);

    return I_beta_DS;

}

////////////////////////////////////////////////////////////////////////////////
///
/// Primary user interface.
/// 
/// @param state       \input  gas and soot state, set by user.
///
/// sets sources.sootSources vector
/// sets sources.gasSources vector
/// sets sources.pahSources vector
///
////////////////////////////////////////////////////////////////////////////////

void sootModel_SECT::setSourceTerms(state &state) {

    size_t k;
    double term;

    //---------- get chemical rates

    double jNuc = nucl->getNucleationSootRate(state);      // #/m3*s
    double kGrw = grow->getGrowthSootRate(state);          // kg/m2*s
    double kOxi = oxid->getOxidationSootRate(state);       // kg/m2*s

    //----------- nucleation terms

    vector<double> Snuc(nsoot, 0.0);                       // #/m3*s in each bin (only bin 0)
    double mNuc = state.cMin*gasSpMW[(int)gasSp::C]/Na;    // mass of a nucleated particle
    Snuc[0]     = jNuc * mNuc /mBins[0];                   // kg_soot/m3*s (as carbon); \todo check that soot nucleation mass < mBins[1]

    //----------- get area for growth, condensation and oxidation

    vector<double> Am2m3(nsoot, 0);                        // m2 soot / m3 bulk volume
    for (k = 0; k < nsoot; k++)
        Am2m3[k] = M_PI*pow(6.*mBins[k]/(M_PI*rhoSoot), twothird)*state.sootVar[k];

    //----------- growth terms: positive velocity through size domain

    vector<double> Sgrw(nsoot, 0.0);                       // #/m3*s in each bin

    k=0;                                                   // first bin
    term = kGrw*Am2m3[k]*state.sootVar[k]/(mBins[k+1]-mBins[k]);
    Sgrw[k] = -term;

    for(k=1; k<nsoot-1; k++) {                             // loop up interior bins
        Sgrw[k]  = term;
        term     = kGrw*Am2m3[k]*state.sootVar[k]/(mBins[k+1]-mBins[k]);
        Sgrw[k] -= term;
    }

    k=nsoot-1;                                             // last bin
    Sgrw[k] = term +                                       // growth into last bin from its smaller neighbor + 
              kGrw*Am2m3[k]*state.sootVar[k]/mBins[k];// growth inside last bin manifest as new particles in that bin

    //----------- PAH condensation terms: 
    //----------- positive vel. through size domain: each bin has in/out except 1st (out) and last (in,gen)
    //----------- beta_DSi is set in pahSootCollisionRatePerDimer called in nucl->getNucleationSootRate

    vector<double> Scnd(nsoot, 0.0);
    if (nucl->mechType == nucleationMech::PAH) {

        k=0;                                               // first bin
        term = beta_DSi[k] * state.sootVar[k] * nucl->DIMER.nDimer * 
               nucl->DIMER.mDimer / (mBins[k+1]-mBins[k]);
        Scnd[k] = -term;

        for(k=1; k<nsoot-1; k++) {                         // loop up interior bins
            Scnd[k]  = term;
            term = beta_DSi[k] * state.sootVar[k] * nucl->DIMER.nDimer * 
                   nucl->DIMER.mDimer / (mBins[k+1]-mBins[k]);
            Scnd[k] -= term;
        }

        k=nsoot-1;                                         // last bin 
        Scnd[k] = term +                                   // growth into bin by neighbor + ... vvv
                  beta_DSi[k] * state.sootVar[k] *    // growth inside last bin, manifest as new particles in that bin (rather that transport out)
                  nucl->DIMER.nDimer * nucl->DIMER.mDimer / mBins[k];
    }

    //----------- oxidation terms: negative velocity through size domain

    vector<double> Soxi(nsoot, 0.0);                       // #/m3*s in each bin
    k=nsoot-1;                                             // last bin
    term = kOxi*Am2m3[k]*state.sootVar[k]/(mBins[k]-mBins[k-1]);
    Soxi[k] = -term;
    for(k=nsoot-2; k>0; k--) {                             // loop down interior bins
        Soxi[k]  = term;
        term     = kOxi*Am2m3[k]*state.sootVar[k]/(mBins[k]-mBins[k-1]);
        Soxi[k] -= term;
    }
    k=0;                                                   // first bin
    Soxi[k] = term -                                       // source from oxid of larger neighbor - 
              kOxi*Am2m3[k]*state.sootVar[k]/mBins[k];// oxidation inside first bin, manifest as fewer particles in that bin (rather than transport out)

    //----------- coagulation terms

    static const double ilnF = 1.0/log(binGrowthFactor);   // factor for finding location

    vector<double> Scoa(nsoot, 0.0);                       // #/m3*s in each bin
    double K12;

    for(size_t i=0; i<nsoot; i++) {                        // loop size i
        for(size_t j=i; j<nsoot; j++) {                    // which collides with each size j >= i (loop over upper triang matrix inc diag)

            //----------- loss: i,j collide to remove from bins i and j

            K12   = coag->getCoagulationSootRate(state, mBins[i], mBins[j]);
            term  = K12*state.sootVar[i]*state.sootVar[j];
            Scoa[i] -= term;
            if (j>i)                   // account for terms below the diagonal taking advantage of symmetry
                Scoa[j] -= term;

            //----------- gain: mi + mj = mk --> bins floor(k) and ceil(k) gain so that mass, # conserved
            //----------- mBins[0]*F^k = mBins[i] + mBins[j] --> k = int( log((mBins[i]+mBins[j])/mBins[0])/log(F) )

            if (i==j) term *= 0.5;

            size_t k  = static_cast<size_t>(ilnF * log((mBins[i]+mBins[j])/mBins[0]));

            if (k >= nsoot) 
                k=nsoot-1;
            if (k == nsoot-1)                              // i+j into last bin, no splitting, conserve mass
                Scoa[k] += term*(mBins[i]+mBins[j])/mBins[k];
            else {                                         // i+j between k and k+1, split to conserve # and mass
                double Xk = (mBins[k+1] - (mBins[i] + mBins[j])) / (mBins[k+1] - mBins[k]);   // fraction into bin k
                Scoa[k]   += Xk       * term;
                Scoa[k+1] += (1.0-Xk) * term;
            }
        }
    }

    //---------- combine to make soot source terms

    for (size_t k=0; k<nsoot; k++)
        sources.sootSources[k] = Snuc[k] + Scoa[k];// + Scnd[k] + Sgrw[k];  // #/m3*s in bin k
        //sources.sootSources[k] = Snuc[k] + Sgrw[k] + Scnd[k] + Soxi[k] + Scoa[k];  // #/m3*s in bin k

    //---------- set gas sources

    double mdotN=0, mdotG=0, mdotO=0;                      // kg/m3*s from nuc, grow, cond, oxid
    for(size_t k=0; k<nsoot; k++) {
        mdotN += Snuc[k]*mBins[k];
        mdotG += Sgrw[k]*mBins[k];
        mdotO += Soxi[k]*mBins[k];
    }

    vector<double> nucl_gasSources((size_t)gasSp::size, 0.0);
    vector<double> grow_gasSources((size_t)gasSp::size, 0.0);
    vector<double> oxid_gasSources((size_t)gasSp::size, 0.0);

    nucl->getNucleationGasRates(mdotN, nucl_gasSources);
    grow->getGrowthGasRates(    mdotG, grow_gasSources);
    oxid->getOxidationGasRates( mdotO, oxid_gasSources);

    for (size_t sp=0; sp<(size_t)gasSp::size; sp++)
        sources.gasSources[sp] = nucl_gasSources[sp] + grow_gasSources[sp] + oxid_gasSources[sp];

    //---------- set PAH source terms

    if(nucl->mechType == nucleationMech::PAH)
        sources.pahSources = nucl->nucleationPahRxnRates;          // includes both nucleation and condensation
}

////////////////////////////////////////////////////////////////////////////////
///
/// \return M0
///
////////////////////////////////////////////////////////////////////////////////

double sootModel_SECT::get_M0_sectional(const state &state) {

    double M0;
    for (size_t k=0; k<nsoot; k++)
        M0 += state.sootVar[k];
    return M0;
}

////////////////////////////////////////////////////////////////////////////////
///
/// \return M1
///
////////////////////////////////////////////////////////////////////////////////

double sootModel_SECT::get_M1_sectional(const state &state) {

    double M1;
    for (size_t k=0; k<nsoot; k++)
        M1 += state.sootVar[k] * mBins[k];
    return M1;
}
