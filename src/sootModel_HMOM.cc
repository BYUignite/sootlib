#include "sootModel_HMOM.h"
#include "binomial.h"
#include <cmath>
#include <algorithm>

using namespace std;
using namespace soot;

// NOTE: THIS HMOM FORMULATION IS UNIVARIATE WITH ONLY 1 INTERNAL COORDINATE (PARTICLE MASS).
// NOTE: SURFACE AREA IS NOT TRANSPORTED AS AN INDEPENDENT VARIABLE

////////////////////////////////////////////////////////////////////////////////
///
/// Constructor taking pointers to chemistry models as input.
///
/// @param nsoot_ \input number of soot moments + 1 weight (4-9).
/// @param nucl_  \input pointer to nucleation model.
/// @param grow_  \input pointer to growth model.
/// @param oxid_  \input pointer to oxidation model.
/// @param coag_  \input pointer to coagulation model.
/// @param Ntar_  \input number of tar variables (0-1).
/// @param tar_   \input pointer to tar model.
///
////////////////////////////////////////////////////////////////////////////////

sootModel_HMOM::sootModel_HMOM(size_t            nsoot_,
                                 nucleationModel  *nucl_,
                                 growthModel      *grow_,
                                 oxidationModel   *oxid_,
                                 coagulationModel *coag_,
                                 size_t            Ntar_,
                                 tarModel         *tar_) :
        sootModel(nsoot_, nucl_, grow_, oxid_, coag_, Ntar_, tar_) {

    if (nsoot_ < 4 || nsoot_ > 9)
        throw runtime_error("HMOM requires 4-9 soot variables (3-8 moments + 1 weight)");

    if ( !(tar->mechType == tarMech::NONE))
        throw runtime_error("HMOM currently does not handle tar models");
    
    if ( !(coag->mechType == coagulationMech::FM        ||
           coag->mechType == coagulationMech::CONTINUUM ||
           coag->mechType == coagulationMech::HM) )
        throw runtime_error("HMOM coagulation requires FM or CONTINUUM or HM");

    psdMechType = psdMech::HMOM;

    Nmom = nsoot_ - 1; // actual number of soot moments

    diffTable_L.resize(Nmom);
    for (size_t k=0; k<Nmom; k++)
        diffTable_L[k] = vector<double>(Nmom-k, 0.0);

    Mp6_L = vector<double>(25, 0.0);
    Mq6_L = vector<double>(33, 0.0);
    np  = {4,4,7,10,13,16,19,22,25};
    nq  = {12,12,15,18,21,24,27,30,33};
}

////////////////////////////////////////////////////////////////////////////////
///
/// Constructor taking enumerations names as input.
///
/// @param nsoot_ \input number of soot moments + 1 weight (4-9).
/// @param Nmech  \input one of enum class nucleationMech in sootDefs.h
/// @param Gmech  \input one of enum class growthMech in sootDefs.h
/// @param Omech  \input one of enum class oxidationMech in sootDefs.h
/// @param Cmech  \input one of enum class coagulationMech in sootDefs.h
/// @param Ntar_  \input number of tar variables (0-1).
/// @param Tmech  \input one of enum class tarMech in sootDefs.h
///
////////////////////////////////////////////////////////////////////////////////

sootModel_HMOM::sootModel_HMOM(size_t          nsoot_,
                                 nucleationMech  Nmech,
                                 growthMech      Gmech,
                                 oxidationMech   Omech,
                                 coagulationMech Cmech,
                                 size_t          Ntar_,
                                 tarMech         Tmech) :
        sootModel(nsoot_, Nmech, Gmech, Omech, Cmech, Ntar_, Tmech) {

    if (nsoot_ < 4 || nsoot_ > 9)
        throw runtime_error("HMOM requires 4-9 soot variables (3-8 moments + 1 weight)");

    if ( !(tar->mechType == tarMech::NONE))
        throw runtime_error("HMOM currently does not handle tar models");
    
    if ( !(coag->mechType == coagulationMech::FM        ||
           coag->mechType == coagulationMech::CONTINUUM ||
           coag->mechType == coagulationMech::HM) )
        throw runtime_error("HMOM coagulation requires FM or CONTINUUM or HM");

    psdMechType = psdMech::HMOM;

    Nmom = nsoot_ - 1;  // actual number of soot moments

    diffTable_L.resize(Nmom);
    for (size_t k=0; k<Nmom; k++)
        diffTable_L[k] = vector<double>(Nmom-k, 0.0);

    Mp6_L = vector<double>(25, 0.0);
    Mq6_L = vector<double>(33, 0.0);
    np  = {4,4,7,10,13,16,19,22,25};
    nq  = {12,12,15,18,21,24,27,30,33};
}

////////////////////////////////////////////////////////////////////////////////
///
/// Primary user interface.
///
////////////////////////////////////////////////////////////////////////////////

void sootModel_HMOM::setSourceTerms(state &state) {

    for (size_t k=0; k<nsoot; k++)
        sources.sootSources[k] = 0.0;

    double N0 = state.sootVar[Nmom];
    double mNuc = state.cMin*gasSpMW[(int)gasSp::C]/Na;

    //---------- Compute large-mode moments M_L
    vector<double> M_L(Nmom, 0.0);
    for (size_t k=0; k<Nmom; k++) {
        M_L[k] = max(state.sootVar[k] - N0*pow(mNuc, double(k)), 0.0);
    }

    // Guard M_L[0] from being too small to prevent log10 errors
    if (M_L[0] <= 0.0) {
        M_L[0] = 1E-20;
    }
    for (size_t k=1; k<Nmom; k++) {
        if (M_L[k] <= 0.0) {
            M_L[k] = M_L[k-1] * mNuc * 1.5; // fallback scaling
        }
    }

    set_diffTable_L(M_L);
    set_fractional_moments_Mp6_Mq6_L();
    set_m0Powers(mNuc);

    //---------- get chemical rates
    double Jnuc = nucl->getNucleationSootRate(state);
    double Kgrw = grow->getGrowthSootRate(state);
    double Koxi = oxid->getOxidationSootRate(state);

    //---------- Nucleation
    vector<double> Mnuc(Nmom, 0.0);
    double N0_nuc = 0.0;
    if (nucl->mechType != nucleationMech::NONE) {
        N0_nuc = Jnuc;
        for (size_t i=0; i<Nmom; i++)
            Mnuc[i] = pow(mNuc, double(i))*Jnuc;
    }

    //--------- Condensation (PAH dimers)
    vector<double> Mcnd(Nmom, 0.0);
    double N0_cond = 0.0;

    if (nucl->mechType == nucleationMech::PAH) {
        double mDimer = nucl->DIMER.mDimer;
        double nDimer = nucl->DIMER.nDimer;

        // Collision rate coefficient of dimer with nucleated particle
        double beta_c0 = coag->getCoagulationSootRate(state, mDimer, mNuc);
        N0_cond = -beta_c0 * nDimer * N0;

        // Condensation on large mode using MOMIC
        double mD26  = pow(mDimer,  2./6.);
        double mDn26 = pow(mDimer, -2./6.);
        double mDn46 = pow(mDimer, -4./6.);
        double mDn36 = pow(mDimer, -3./6.);
        double mDn16 = pow(mDimer, -1./6.);
        double mD16  = pow(mDimer,  1./6.);
        double mD36  = pow(mDimer,  3./6.);
        double mD56  = pow(mDimer,  5./6.);
        double mD76  = pow(mDimer,  7./6.);
        double mD96  = pow(mDimer,  9./6.);
        double mD116 = pow(mDimer, 11./6.);
        double mD136 = pow(mDimer, 13./6.);
        double mD156 = pow(mDimer, 15./6.);
        double mD176 = pow(mDimer, 17./6.);
        double mD196 = pow(mDimer, 19./6.);

        auto g_grid_dimer_L = [&](int y) {
            int yi = (y-1)*3;
            double g0 = mD16 * Mq6_L[yi+0] + 2.*mDn16 * Mq6_L[yi+1] + mDn36 * Mq6_L[yi+2];
            double g1 = mD76 * Mq6_L[yi+0] + 2.*mD56 * Mq6_L[yi+1] + mD36 * Mq6_L[yi+2] + mD16 * Mq6_L[yi+3] + 2.*mDn16 * Mq6_L[yi+4] + mDn36 * Mq6_L[yi+5];
            double g2 = 0.0;
            if (y<=3)
                g2 = mD136 * Mq6_L[yi+0] + 2.*mD116 * Mq6_L[yi+1] + mD96 * Mq6_L[yi+2] + 2.*mD76 * Mq6_L[yi+3] + 4.*mD56 * Mq6_L[yi+4] + 2.*mD36 * Mq6_L[yi+5] + mD16 * Mq6_L[yi+6] + 2.*mDn16 * Mq6_L[yi+7] + mDn36 * Mq6_L[yi+8];
            double g3 = 0.0;
            if (y<=2)
                g3 = mD196 * Mq6_L[yi+0] + 2.*mD176 * Mq6_L[yi+1] + mD156 * Mq6_L[yi+2] + 3.*mD136 * Mq6_L[yi+3] + 6.*mD116 * Mq6_L[yi+4] + 3.*mD96 * Mq6_L[yi+5] + 3.*mD76 * Mq6_L[yi+6] + 6.*mD56 * Mq6_L[yi+7] + 3.*mD36 * Mq6_L[yi+8] + mD16 * Mq6_L[yi+9] + 2.*mDn16 * Mq6_L[yi+10] + mDn36 * Mq6_L[yi+11];

            double ghalf;
            if (y<=2)
                ghalf = pow(g0,5./16.) * pow(g1,15./16.) * pow(g2, -5./16.) * pow(g3, 1./16.);
            else if (y<=3)
                ghalf = pow(g0, 3./8.) * pow(g1,  3./4.) * pow(g2,  -1./8.);
            else
                ghalf = pow(g0, 1./2.) * pow(g1,  1./2.);
            return ghalf;
        };

        const double Kc  = coag->getKc(state);
        const double Kcp = coag->getKcp(state);
        const double Kfm = coag->getKfm(state);

        for (size_t k=1; k<Nmom; k++) {
            size_t kk = (k-1)*3;
            double Mcnd_C = double(k)*Kc*nDimer*mDimer* (  
                                       mD26*Mp6_L[kk+1]  +
                                          2.*Mp6_L[kk+2] +
                                       mDn26*Mp6_L[kk+3] +
                                       Kcp*( mD26*Mp6_L[kk+0] +
                                                  Mp6_L[kk+1] +
                                            mDn26*Mp6_L[kk+2] +
                                            mDn46*Mp6_L[kk+3] ) );

            double Mcnd_FM = double(k)*Kfm*nDimer*mDimer*g_grid_dimer_L(k);
            double Mcnd_L_k = Mcnd_FM*Mcnd_C / (Mcnd_FM+Mcnd_C);

            Mcnd[k] = double(k)*pow(mNuc, double(k-1))*beta_c0*nDimer*mDimer*N0 + Mcnd_L_k;
        }
    }

    //---------- Surface growth 
    
    vector<double> Mgrw(Nmom, 0.0);
    vector<double> Moxi(Nmom, 0.0);
    const double Acoef = M_PI * pow(6./(M_PI*rhoSoot), twothird);

    double N0_sg = 0.0;
    double N0_ox = 0.0;

    if (grow->mechType != growthMech::NONE) {
        N0_sg = -Kgrw * Acoef * pow(mNuc, -1.0/3.0) * N0;
        for (size_t k=1; k<Nmom; k++) {
            Mgrw[k] = Kgrw * Acoef * double(k) * (pow(mNuc, double(k) - onethird)*N0 + Mr_L(double(k) - onethird));
        }
    }
    
    //---------- Oxidation
    
    if (oxid->mechType != oxidationMech::NONE) {
        N0_ox = -Koxi * Acoef * pow(mNuc, -1.0/3.0) * N0;
        for (size_t k=1; k<Nmom; k++) {
            Moxi[k] = -Koxi * Acoef * double(k) * (pow(mNuc, double(k) - onethird)*N0 + Mr_L(double(k) - onethird));
        }
    }

    //---------- Coagulation
    vector<double> Mcoa(Nmom, 0.0);
    double N0_coag = 0.0;

    if (coag->mechType != coagulationMech::NONE) {
        double beta_00 = coag->getCoagulationSootRate(state, mNuc, mNuc);
        double N0_coag_SS = -beta_00 * N0 * N0;

        double beta_0L = get_Ik(0, state, mNuc);
        double N0_coag_SL = -beta_0L * N0;

        N0_coag = N0_coag_SS + N0_coag_SL;

        // Large-large coagulation
        vector<double> Mcoa_LL = HMOMCoagulationRates_LL(state, M_L);

        for (size_t r=0; r<Nmom; r++) {
            if (r == 1) continue; // mass conserved

            double Mcoa_SS_r = 0.5 * beta_00 * N0 * N0 * (pow(2.0, double(r)) - 2.0) * pow(mNuc, double(r));

            double Mcoa_SL_r = 0.0;
            if (r >= 2) {
                double sum_SL = 0.0;
                for (size_t k=1; k<=r-1; k++) {
                    sum_SL += binomial_coefficient(r, k) * pow(mNuc, double(r-k)) * get_Ik(k, state, mNuc);
                }
                Mcoa_SL_r = N0 * sum_SL;
            } else if (r == 0) {
                Mcoa_SL_r = -beta_0L * N0;
            }

            Mcoa[r] = Mcoa_SS_r + Mcoa_SL_r + Mcoa_LL[r];
        }
    }

    //---------- Combine to make soot source terms
    for (size_t r=0; r<Nmom; r++) {
        sources.sootSources[r] = Mnuc[r] + Mcnd[r] + Mgrw[r] + Moxi[r] + Mcoa[r];
    }
    sources.sootSources[Nmom] = N0_nuc + N0_cond + N0_sg + N0_ox + N0_coag;

    //---------- set gas source terms
    vector<double> nucl_gasSources((size_t)gasSp::size, 0.0);
    vector<double> grow_gasSources((size_t)gasSp::size, 0.0);
    vector<double> oxid_gasSources((size_t)gasSp::size, 0.0);

    nucl->getNucleationGasRates(Mnuc[1], nucl_gasSources);
    grow->getGrowthGasRates(    Mgrw[1], grow_gasSources);
    oxid->getOxidationGasRates( Moxi[1], oxid_gasSources);

    for (size_t sp=0; sp<(size_t)gasSp::size; sp++)
        sources.gasSources[sp] = nucl_gasSources[sp] + grow_gasSources[sp] + oxid_gasSources[sp];

    //---------- set PAH source terms
    if(nucl->mechType == nucleationMech::PAH)
        sources.pahSources = nucl->nucleationPahRxnRates;
}

////////////////////////////////////////////////////////////////////////////////
///
/// Compute PAH condensation terms for HMOM model.
///
////////////////////////////////////////////////////////////////////////////////

double sootModel_HMOM::pahSootCollisionRatePerDimer(const state &state, const double mDimer) {

    if (nucl->mechType != nucleationMech::PAH)
        return 0.0;

    double N0 = state.sootVar[Nmom];
    double mNuc = state.cMin*gasSpMW[(int)gasSp::C]/Na;

    // Collision rate with small mode particles
    double beta_c0 = coag->getCoagulationSootRate(state, mDimer, mNuc);
    double I_S = beta_c0 * N0;

    // Collision rate with large mode particles using MOMIC
    double mD26  = pow(mDimer,  2./6.);
    double mDn26 = pow(mDimer, -2./6.);
    double mDn46 = pow(mDimer, -4./6.);
    double mDn36 = pow(mDimer, -3./6.);
    double mDn16 = pow(mDimer, -1./6.);
    double mD16  = pow(mDimer,  1./6.);
    double mD36  = pow(mDimer,  3./6.);
    double mD56  = pow(mDimer,  5./6.);
    double mD76  = pow(mDimer,  7./6.);
    double mD96  = pow(mDimer,  9./6.);
    double mD116 = pow(mDimer, 11./6.);
    double mD136 = pow(mDimer, 13./6.);
    double mD156 = pow(mDimer, 15./6.);
    double mD176 = pow(mDimer, 17./6.);
    double mD196 = pow(mDimer, 19./6.);

    const double Kc  = coag->getKc(state);
    const double Kcp = coag->getKcp(state);
    const double Kfm = coag->getKfm(state);

    double Ic1_L = Kc * (  
                  mD26*Mp6_L[1] +
                    2.*Mp6_L[2] +
                 mDn26*Mp6_L[3] +
                 Kcp*( mD26*Mp6_L[0] +
                            Mp6_L[1] +
                      mDn26*Mp6_L[2] +
                      mDn46*Mp6_L[3] ) );

    auto g_grid_dimer_L = [&](int y) {
        int yi = (y-1)*3;
        double g0 = mD16 * Mq6_L[yi+0] + 2.*mDn16 * Mq6_L[yi+1] + mDn36 * Mq6_L[yi+2];
        double g1 = mD76 * Mq6_L[yi+0] + 2.*mD56 * Mq6_L[yi+1] + mD36 * Mq6_L[yi+2] + mD16 * Mq6_L[yi+3] + 2.*mDn16 * Mq6_L[yi+4] + mDn36 * Mq6_L[yi+5];
        double g2 = 0.0;
        if (y<=3)
            g2 = mD136 * Mq6_L[yi+0] + 2.*mD116 * Mq6_L[yi+1] + mD96 * Mq6_L[yi+2] + 2.*mD76 * Mq6_L[yi+3] + 4.*mD56 * Mq6_L[yi+4] + 2.*mD36 * Mq6_L[yi+5] + mD16 * Mq6_L[yi+6] + 2.*mDn16 * Mq6_L[yi+7] + mDn36 * Mq6_L[yi+8];
        double g3 = 0.0;
        if (y<=2)
            g3 = mD196 * Mq6_L[yi+0] + 2.*mD176 * Mq6_L[yi+1] + mD156 * Mq6_L[yi+2] + 3.*mD136 * Mq6_L[yi+3] + 6.*mD116 * Mq6_L[yi+4] + 3.*mD96 * Mq6_L[yi+5] + 3.*mD76 * Mq6_L[yi+6] + 6.*mD56 * Mq6_L[yi+7] + 3.*mD36 * Mq6_L[yi+8] + mD16 * Mq6_L[yi+9] + 2.*mDn16 * Mq6_L[yi+10] + mDn36 * Mq6_L[yi+11];

        double ghalf;
        if (y<=2)
            ghalf = pow(g0,5./16.) * pow(g1,15./16.) * pow(g2, -5./16.) * pow(g3, 1./16.);
        else if (y<=3)
            ghalf = pow(g0, 3./8.) * pow(g1,  3./4.) * pow(g2,  -1./8.);
        else
            ghalf = pow(g0, 1./2.) * pow(g1,  1./2.);
        return ghalf;
    };

    double Ifm1_L = Kfm*g_grid_dimer_L(1);
    double I_L = Ifm1_L*Ic1_L/(Ifm1_L + Ic1_L);

    return I_S + I_L;
}

////////////////////////////////////////////////////////////////////////////////
///
/// private helper methods
///
////////////////////////////////////////////////////////////////////////////////

void sootModel_HMOM::set_diffTable_L(const vector<double> &M_L) {
    for (size_t k=0; k<Nmom; k++)
        diffTable_L[k][0] = log10(M_L[k]);

    for (size_t j=1; j<Nmom; j++)
        for (size_t i=0; i<Nmom-j; i++)
            diffTable_L[i][j] = diffTable_L[i+1][j-1] - diffTable_L[i][j-1];
}

double sootModel_HMOM::Mr_L(const double r) {
    double l10Mr = diffTable_L[0][0];
    double coef = r;
    int kend = (r >= 0) ? Nmom : 3;
    for(int k=1; k<kend; k++) {
        l10Mr += coef*diffTable_L[0][k];
        coef *= (r-k)/double(k+1);
    }

    double value = pow(10., l10Mr);
    return isfinite(value) ? value : 0.0;
}

void sootModel_HMOM::set_fractional_moments_Mp6_Mq6_L() {
    double p = -4;
    for(size_t i=0; i<np[Nmom]; i++, p+=2)
        Mp6_L[i] = Mr_L(p/6.0);

    double q = -3;
    for(size_t i=0; i<nq[Nmom]; i++, q+=2)
        Mq6_L[i] = Mr_L(q/6.0);
}

void sootModel_HMOM::set_m0Powers(double m0) {
    m0_26  = pow(m0,  2./6.);
    m0_n26 = pow(m0, -2./6.);
    m0_n46 = pow(m0, -4./6.);

    m0_n36  = pow(m0,  -3./6.);
    m0_n16  = pow(m0,  -1./6.);
    m0_16   = pow(m0,   1./6.);
    m0_36   = pow(m0,   3./6.);
    m0_56   = pow(m0,   5./6.);
    m0_76   = pow(m0,   7./6.);
    m0_96   = pow(m0,   9./6.);
    m0_116  = pow(m0,  11./6.);
    m0_136  = pow(m0,  13./6.);
    m0_156  = pow(m0,  15./6.);
    m0_176  = pow(m0,  17./6.);
    m0_196  = pow(m0,  19./6.);
}

double sootModel_HMOM::g_grid_L(int y) {
    int yi = (y-1)*3;
    double g0, g1, g2, g3;

    g0 =            m0_16   * Mq6_L[yi+0] +
                 2.*m0_n16  * Mq6_L[yi+1] + 
                    m0_n36  * Mq6_L[yi+2];

    g1 =            m0_76   * Mq6_L[yi+0] +  
                 2.*m0_56   * Mq6_L[yi+1] +
                    m0_36   * Mq6_L[yi+2] +
                    m0_16   * Mq6_L[yi+3] +
                 2.*m0_n16  * Mq6_L[yi+4] +
                    m0_n36  * Mq6_L[yi+5] ;

    if (y<=3)    
        g2 =        m0_136  * Mq6_L[yi+0] +  
                 2.*m0_116  * Mq6_L[yi+1] +
                    m0_96   * Mq6_L[yi+2] +
                 2.*m0_76   * Mq6_L[yi+3] +
                 4.*m0_56   * Mq6_L[yi+4] +
                 2.*m0_36   * Mq6_L[yi+5] +
                    m0_16   * Mq6_L[yi+6] +
                 2.*m0_n16  * Mq6_L[yi+7] +
                    m0_n36  * Mq6_L[yi+8] ;

    if (y<=2)    
        g3 =        m0_196 * Mq6_L[yi+0] +  
                 2.*m0_176 * Mq6_L[yi+1] +
                    m0_156 * Mq6_L[yi+2]  +
                 3.*m0_136 * Mq6_L[yi+3]  +
                 6.*m0_116 * Mq6_L[yi+4]  +
                 3.*m0_96  * Mq6_L[yi+5]  +
                 3.*m0_76  * Mq6_L[yi+6]  +
                 6.*m0_56  * Mq6_L[yi+7]  +
                 3.*m0_36  * Mq6_L[yi+8]  +
                    m0_16  * Mq6_L[yi+9]  +
                 2.*m0_n16 * Mq6_L[yi+10]  +
                    m0_n36 * Mq6_L[yi+11]  ;

    double ghalf;
    if (y<=2)
        ghalf = pow(g0,5./16.) * pow(g1,15./16.) * pow(g2, -5./16.) * pow(g3, 1./16.);
    else if (y<=3)
        ghalf = pow(g0, 3./8.) * pow(g1,  3./4.) * pow(g2,  -1./8.);
    else
        ghalf = pow(g0, 1./2.) * pow(g1,  1./2.);

    return ghalf;
}

double sootModel_HMOM::f_grid_L(int x, int y) {
    int xi = x*3;
    int yi = y*3;
    double f0, f1, f2, f3;

    if (x==y) {
        f0 = 2.*(       Mq6_L[xi+0]  * Mq6_L[yi+2] +
                        Mq6_L[xi+1]  * Mq6_L[yi+1] );

        f1 = 2.*(       Mq6_L[xi+0]  * Mq6_L[yi+5] +  
                     2.*Mq6_L[xi+1]  * Mq6_L[yi+4] +
                        Mq6_L[xi+2]  * Mq6_L[yi+3] );

        if (y<=3)
            f2 = 2.*(   Mq6_L[xi+0]  * Mq6_L[yi+8] +  
                     2.*Mq6_L[xi+1]  * Mq6_L[yi+7] +
                        Mq6_L[xi+2]  * Mq6_L[yi+6] +
                     2.*Mq6_L[xi+3]  * Mq6_L[yi+5] +
                     2.*Mq6_L[xi+4]  * Mq6_L[yi+4] );

        if (y<=2)
            f3 = 2.*(   Mq6_L[xi+0]  * Mq6_L[yi+11] +  
                     2.*Mq6_L[xi+1]  * Mq6_L[yi+10] +
                        Mq6_L[xi+2]  * Mq6_L[yi+9]  +
                     3.*Mq6_L[xi+3]  * Mq6_L[yi+8]  +
                     6.*Mq6_L[xi+4]  * Mq6_L[yi+7]  +
                     3.*Mq6_L[xi+5]  * Mq6_L[yi+6] );
    }
    else {
        f0 =            Mq6_L[xi+0]  * Mq6_L[yi+2] +
                     2.*Mq6_L[xi+1]  * Mq6_L[yi+1] + 
                        Mq6_L[xi+2]  * Mq6_L[yi+0];

        f1 =            Mq6_L[xi+0]  * Mq6_L[yi+5] +  
                     2.*Mq6_L[xi+1]  * Mq6_L[yi+4] +
                        Mq6_L[xi+2]  * Mq6_L[yi+3] +
                        Mq6_L[xi+3]  * Mq6_L[yi+2] +
                     2.*Mq6_L[xi+4]  * Mq6_L[yi+1] +
                        Mq6_L[xi+5]  * Mq6_L[yi+0] ;

        if (y<=3)    
            f2 =        Mq6_L[xi+0]  * Mq6_L[yi+8] +  
                     2.*Mq6_L[xi+1]  * Mq6_L[yi+7] +
                        Mq6_L[xi+2]  * Mq6_L[yi+6] +
                     2.*Mq6_L[xi+3]  * Mq6_L[yi+5] +
                     4.*Mq6_L[xi+4]  * Mq6_L[yi+4] +
                     2.*Mq6_L[xi+5]  * Mq6_L[yi+3] +
                        Mq6_L[xi+6]  * Mq6_L[yi+2] +
                     2.*Mq6_L[xi+7]  * Mq6_L[yi+1] +
                        Mq6_L[xi+8]  * Mq6_L[yi+0] ;

        if (y<=2)    
            f3 =        Mq6_L[xi+0]  * Mq6_L[yi+11] +  
                     2.*Mq6_L[xi+1]  * Mq6_L[yi+10] +
                        Mq6_L[xi+2]  * Mq6_L[yi+9]  +
                     3.*Mq6_L[xi+3]  * Mq6_L[yi+8]  +
                     6.*Mq6_L[xi+4]  * Mq6_L[yi+7]  +
                     3.*Mq6_L[xi+5]  * Mq6_L[yi+6]  +
                     3.*Mq6_L[xi+6]  * Mq6_L[yi+5]  +
                     6.*Mq6_L[xi+7]  * Mq6_L[yi+4]  +
                     3.*Mq6_L[xi+8]  * Mq6_L[yi+3]  +
                        Mq6_L[xi+9]  * Mq6_L[yi+2]  +
                     2.*Mq6_L[xi+10] * Mq6_L[yi+1]  +
                        Mq6_L[xi+11] * Mq6_L[yi+0]  ;
    }

    double fhalf;
    if (y<=2)
        fhalf = pow(f0,5./16.) * pow(f1,15./16.) * pow(f2, -5./16.) * pow(f3, 1./16.);
    else if (y<=3)
        fhalf = pow(f0, 3./8.) * pow(f1,  3./4.) * pow(f2,  -1./8.);
    else
        fhalf = pow(f0, 1./2.) * pow(f1,  1./2.);

    return fhalf;
}

double sootModel_HMOM::get_Ik(int k, const state &state, double m0) {
    const double Kc  = coag->getKc(state);
    const double Kcp = coag->getKcp(state);
    const double Kfm = coag->getKfm(state);

    // Free molecular integral
    double I_k_FM = Kfm * g_grid_L(k);

    // Continuum integral
    size_t kk = k * 3;
    double I_k_C = Kc * ( m0_26 * Mp6_L[kk+1] + 2.0 * Mp6_L[kk+2] + m0_n26 * Mp6_L[kk+3] + 
                          Kcp * ( m0_26 * Mp6_L[kk+0] + Mp6_L[kk+1] + m0_n26 * Mp6_L[kk+2] + m0_n46 * Mp6_L[kk+3] ) );

    if (coag->mechType == coagulationMech::FM)
        return I_k_FM;
    else if (coag->mechType == coagulationMech::CONTINUUM)
        return I_k_C;
    else // harmonic mean
        return I_k_FM * I_k_C / (I_k_FM + I_k_C);
}

vector<double> sootModel_HMOM::HMOMCoagulationRates_LL(const state& state, const vector<double>& M_L) {
    if (M_L[0] <= 0.0) return vector<double>(Nmom, 0.0);

    vector<double> Rates_C(Nmom, 0.0);
    vector<double> Rates_FM(Nmom, 0.0);
    vector<double> Rates(Nmom, 0.0);

    //----------- free-molecular regime
    if (coag->mechType == coagulationMech::FM || 
        coag->mechType == coagulationMech::HM) {

        const double Kfm = coag->getKfm(state);

        for (size_t r=0; r<Nmom; r++) {
            if (r==1) continue; 
            if (r==0)
                Rates_FM[r] = -0.5*Kfm*f_grid_L(0,0);
            else {
                for (size_t k=1; k<=r-1; k++)
                    Rates_FM[r] += binomial_coefficient(r,k) * f_grid_L(k, r-k);
                Rates_FM[r] *= 0.5*Kfm;
            }
        }
    }

    //----------- continuum regime
    if (coag->mechType == coagulationMech::CONTINUUM || 
        coag->mechType == coagulationMech::HM) {

        const double Kc  = coag->getKc(state);
        const double Kcp = coag->getKcp(state);

        for (size_t r=0; r<Nmom; r++) {
            if (r==1) continue; 
            if (r==0)
                Rates_C[r] = -Kc*( Mp6_L[2]*Mp6_L[2] + Mp6_L[1]*Mp6_L[3] +
                                   Kcp*( Mp6_L[1]*Mp6_L[2] + Mp6_L[0]*Mp6_L[3] ) );
            else {
                size_t kk, rk;
                for (size_t k=1; k<=r-1; k++) {
                    kk = k*3;
                    rk = (r-k)*3;
                    Rates_C[r] = binomial_coefficient(r,k) * (
                                       Mp6_L[kk+1]*Mp6_L[rk+3] +
                                 2.0*  Mp6_L[kk+2]*Mp6_L[rk+2] +
                                       Mp6_L[kk+3]*Mp6_L[rk+1] +
                                 Kcp*( Mp6_L[kk+0]*Mp6_L[rk+3] +
                                       Mp6_L[kk+1]*Mp6_L[rk+2] +
                                       Mp6_L[kk+2]*Mp6_L[rk+1] +
                                       Mp6_L[kk+3]*Mp6_L[rk+0] ) );
                }
                Rates_C[r] *= 0.5*Kc;
            }
        }
    }

    //----------- finalize and return
    for (size_t r=0; r<Nmom; r++) {
        if (r==1) continue;
        if (coag->mechType == coagulationMech::FM)
            Rates[r] = Rates_FM[r];
        else if (coag->mechType == coagulationMech::CONTINUUM)
            Rates[r] = Rates_C[r];
        else
            Rates[r] = Rates_FM[r]*Rates_C[r] / (Rates_FM[r]+Rates_C[r]);
    }

    return Rates;
}
