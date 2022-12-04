#include "sootModel_SECT.h"

using namespace std;
using namespace soot;

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
}

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
}

////////////////////////////////////////////////////////////////////////////////
/** Set the sectional mass coordinate locations: mass per particle at each size location
 */

void sootModel_SECT::set_mBins(const int cMin_) {

    mBins.resize(nsoot);
    for (size_t k = 0; k < nsoot; k++)
        mBins[k] = cMin_ * pow(binGrowthFactor, k) * gasSpMW[(size_t)gasSp::C] / Na;
}

////////////////////////////////////////////////////////////////////////////////

void sootModel_SECT::getSourceTerms(state &state, 
                                    std::vector<double> &sootSources,
                                    std::vector<double> &gasSources,
                                    std::vector<double> &pahSources) const {

    size_t k;
    double term;

    //---------- get chemical rates

    double jNuc = nucl->getNucleationSootRate(state);      // #/m3*s
    double kGrw = grow->getGrowthSootRate(state);          // kg/m2*s
    double kOxi = oxid->getOxidationSootRate(state);       // kg/m2*s

    //----------- nucleation terms

    vector<double> Snuc(nsoot, 0.0);                             // #/m3*s in each bin (only bin 0)
    Snuc[0] = jNuc;

    //----------- get area for growth, condensation and oxidation

    vector<double> Am2m3(nsoot, 0);                                     // m2 soot / m3 bulk volume
    for (k = 0; k < nsoot; k++)
        Am2m3[k] = M_PI*pow(6.*mBins[k]/(M_PI*rhoSoot), twothird)*abs(state.sootVar[k]);

    //----------- growth terms: positive velocity through size domain

    vector<double> Sgrw(nsoot, 0.0);                                    // #/m3*s in each bin
    k=0;                                                                // first bin
    term = kGrw*Am2m3[k]*abs(state.sootVar[k])/(mBins[k+1]-mBins[k]);
    Sgrw[k] = -term;
    for(k=1; k<nsoot-1; k++) {                                          // loop up interior bins
        Sgrw[k]  = term;
        term     = kGrw*Am2m3[k]*abs(state.sootVar[k])/(mBins[k+1]-mBins[k]);
        Sgrw[k] -= term;
    }
    k=nsoot-1;                                                          // last bin
    Sgrw[nsoot-1] = term;

    //----------- PAH condensation terms: positive velocity through size domain

    vector<double> Scnd(nsoot, 0.0);
    if (nucl->mechType == nucleationMech::PAH) {
        k=0;                                                                // first bin
        term = coag->getCoagulationSootRate(state, nucl->DIMER.mDimer, mBins[k])*
               abs(state.sootVar[k]) * nucl->DIMER.nDimer * nucl->DIMER.mDimer / 
               (mBins[k+1]-mBins[k]);
        Scnd[k] = -term;
        for(k=1; k<nsoot-1; k++) {                                          // loop up interior bins
            Scnd[k]  = term;
            term = coag->getCoagulationSootRate(state, nucl->DIMER.mDimer, mBins[k])*
                   abs(state.sootVar[k]) * nucl->DIMER.nDimer * nucl->DIMER.mDimer / 
                   (mBins[k+1]-mBins[k]);
            Scnd[k] -= term;
        }
        k=nsoot-1;                                                          // last bin
        Scnd[nsoot-1] = term;
    }

    //----------- oxidation terms: negative velocity through size domain

    vector<double> Soxi(nsoot, 0.0);                                    // #/m3*s in each bin
    k=nsoot-1;                                                          // last bin
    term = kOxi*Am2m3[k]*abs(state.sootVar[k])/(mBins[k]-mBins[k-1]);
    Soxi[k] = -term;
    for(k=nsoot-2; k>0; k--) {                                          // loop down interior bins
        Soxi[k]  = term;
        term     = kOxi*Am2m3[k]*abs(state.sootVar[k])/(mBins[k]-mBins[k-1]);
        Soxi[k] -= term;
    }
    k=0;                                                                // first bin
    Soxi[k] = term;

    //----------- coagulation terms

    static const double ilnF = 1.0/log(binGrowthFactor);                // factor for finding location

    vector<double> Scoa(nsoot, 0.0);                                    // #/m3*s in each bin
    double K12;

    for(size_t i=0; i<nsoot; i++) {                     // loop size i
        for(size_t j=i; j<nsoot; j++) {                 // which collides with each size j

            //----------- loss: i,j collide to remove from bins i and j

            K12   = coag->getCoagulationSootRate(state, mBins[i], mBins[j]);
            term  = K12*state.sootVar[i]*state.sootVar[j];
            Scoa[i] -= term;
            if (j>i)
                Scoa[j] -= term;

            //----------- gain: mi + mj = mk --> bins floor(k) and ceil(k) gain so that mass, # conserved
            //----------- cmin*F^k = mBins[i] + mBins[j] --> k = int( log((mBins[i]+mbins[j])/cmin)/log(F) )

            if (i==j) term *= 0.5;

            size_t k  = static_cast<size_t>(ilnF * log((mBins[i]+mBins[j])/state.cMin));

            if (k >= nsoot) k=nsoot-1;
            if (k == nsoot-1)            // i+j into last bin, no splitting, conserve mass
                Scoa[k] += term*(mBins[i]+mBins[j])/mBins[k];
            else {                       // i+j between k and k+1, split to conserve # and mass
                double Xk = (mBins[k+1] - (mBins[i] + mBins[j])) / (mBins[k+1] - mBins[k]);   // fraction into bin k
                Scoa[k]   += Xk       * term;
                Scoa[k+1] += (1.0-Xk) * term;
            }
        }
    }

    //---------- combine to make soot source terms

    for (size_t k=0; k<nsoot; k++)
        sootSources[k] = Snuc[k] + Sgrw[k] + Scnd[k] + Soxi[k] + Scoa[k];  // #/m3*s in bin k

    //---------- set gas sources

    double mdotN=0, mdotG=0, mdotO=0;             // kg/m3*s from nuc, grow, cond, oxid
    for(size_t k=0; k<nsoot; k++) {
        mdotN += Snuc[k]*mBins[k];
        mdotG += Sgrw[k]*mBins[k];
        mdotO += Soxi[k]*mBins[k];        // todo verify sign
    }

    vector<double> nucl_gasSources((size_t)gasSp::size, 0.0);
    vector<double> grow_gasSources((size_t)gasSp::size, 0.0);
    vector<double> oxid_gasSources((size_t)gasSp::size, 0.0);

    nucl->getNucleationGasRates(state, mdotN, nucl_gasSources);
    grow->getGrowthGasRates(    state, mdotG, grow_gasSources);
    oxid->getOxidationGasRates( state, mdotO, oxid_gasSources);

    for (size_t sp=0; sp<(size_t)gasSp::size; sp++)
        gasSources[sp] = nucl_gasSources[sp] + grow_gasSources[sp] + oxid_gasSources[sp];

    //---------- set PAH source terms

    if(nucl->mechType == nucleationMech::PAH)
        pahSources = nucl->nucleationPahRxnRates;        // includes both nucleation and condensation
}

