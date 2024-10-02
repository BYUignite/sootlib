#include "sootModel_MOMIC.h"
#include "binomial.h"
#include <cmath>                 //isfinite (not nan or inf)

using namespace std;
using namespace soot;

////////////////////////////////////////////////////////////////////////////////
///
/// Constructor taking pointers to chemistry models as input.
/// User creates these pointers nominally by "new-ing" them.
///
/// @param nsoot_ \input number of soot moments (3-8).
/// @param nucl_  \input pointer to nucleation model.
/// @param grow_  \input pointer to growth model.
/// @param oxid_  \input pointer to oxidation model.
/// @param coag_  \input pointer to coagulation model.
///
////////////////////////////////////////////////////////////////////////////////

sootModel_MOMIC::sootModel_MOMIC(size_t            nsoot_,
                                 nucleationModel  *nucl_,
                                 growthModel      *grow_,
                                 oxidationModel   *oxid_,
                                 coagulationModel *coag_) :
        sootModel(nsoot_, nucl_, grow_, oxid_, coag_) {

    if (nsoot_ < 3 || nsoot_ > 8)
        throw runtime_error("MOMIC requires 3-8 moments");

    if ( !(coag->mechType == coagulationMech::FM        ||
           coag->mechType == coagulationMech::CONTINUUM ||
           coag->mechType == coagulationMech::HM) )
        throw runtime_error("MOMIC coagulation requires FM or CONTINUUM or HM");

    psdMechType = psdMech::MOMIC;

    diffTable.resize(nsoot);
    for (size_t k=0; k<nsoot; k++)
        diffTable[k] = vector<double>(nsoot-k, 0.0);

    Nmom = nsoot;

    Mp6 = vector<double>(22, 0.0);
    Mq6 = vector<double>(30, 0.0);
    np  = {4,4,7,10,13,16,19,22};
    nq  = {12,12,15,18,21,24,27,30};
}

////////////////////////////////////////////////////////////////////////////////
///
/// Constructor taking enumerations names as input.
/// Chemistry pointers are created (new-ed) here based on those enumerations.
///
/// @param nsoot_ \input number of soot moments (3-8).
/// @param Nmech  \input one of enum class nucleationMech in sootDefs.h
/// @param Gmech  \input one of enum class growthMech in sootDefs.h
/// @param Omech  \input one of enum class oxidationMech in sootDefs.h
/// @param Cmech  \input one of enum class coagulationMech in sootDefs.h
///
///
////////////////////////////////////////////////////////////////////////////////

sootModel_MOMIC::sootModel_MOMIC(size_t          nsoot_,
                                 nucleationMech  Nmech,
                                 growthMech      Gmech,
                                 oxidationMech   Omech,
                                 coagulationMech Cmech) :
        sootModel(nsoot_, Nmech, Gmech, Omech, Cmech) {

    if (nsoot_ < 3 || nsoot_ > 8)
        throw runtime_error("MOMIC requires 3-8 moments");

    if ( !(coag->mechType == coagulationMech::FM        ||
           coag->mechType == coagulationMech::CONTINUUM ||
           coag->mechType == coagulationMech::HM) )
        throw runtime_error("MOMIC coagulation requires FM or CONTINUUM or HM");

    psdMechType = psdMech::MOMIC;

    diffTable.resize(nsoot);
    for (size_t k=0; k<nsoot; k++)
        diffTable[k] = vector<double>(nsoot-k, 0.0);

    Nmom = nsoot;

    Mp6 = vector<double>(22, 0.0);
    Mq6 = vector<double>(30, 0.0);
    np  = {4,4,7,10,13,16,19,22};
    nq  = {12,12,15,18,21,24,27,30};
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
/// Assumes mDn36, etc. (mDimer^powers) have been set in set_mDimerPowers().
///
////////////////////////////////////////////////////////////////////////////////

void sootModel_MOMIC::setSourceTerms(state &state) {


    for (size_t k=0; k<nsoot; k++)
        sources.sootSources[k] = 0.0;         // reset to zero, in case downselectIfNeeded reduces Nmom

    //----------

    vector<double> Mtemp = state.sootVar;

    //doldb downselectIfNeeded(Mtemp);

    set_diffTable(Mtemp);

    set_fractional_moments_Mp6_Mq6();                    // set fractional_moment_arrays

    //---------- get chemical rates

    double Jnuc = nucl->getNucleationSootRate(state);
    double Kgrw = grow->getGrowthSootRate(state);
    double Koxi = oxid->getOxidationSootRate(state);

    //---------- nucleation terms

    vector<double> Mnuc(Nmom, 0);

    if (nucl->mechType != nucleationMech::NONE) {
        double m_nuc = state.cMin*gasSpMW[(int)gasSp::C]/Na;
        for (size_t i=0; i<Nmom; i++)
            Mnuc[i] = pow(m_nuc, i)*Jnuc;
    }

    //---------- PAH condensation terms

    vector<double> Mcnd(Nmom, 0);

    if (nucl->mechType == nucleationMech::PAH) {

        //set_mDimerPowers();      // not needed here (called in pahSootCollisionRatePerDimer in nucl PAH)

        vector<double> Mcnd_C(Nmom, 0);
        vector<double> Mcnd_FM(Nmom, 0);

        //------ continuum

        const double Kc  = coag->getKc(state);
        const double Kcp = coag->getKcp(state);

        double mDimer = nucl->DIMER.mDimer;
        double nDimer = nucl->DIMER.nDimer;

        for (size_t k=1, kk=(k-1)*3; k<Nmom; k++)                   // skip moment 0 (no growth term)
            Mcnd_C[k] = double(k)*Kc*nDimer*mDimer* (  
                                       mD26*Mp6[kk+1]  +            //  mD26*M_{k-1-2/6}
                                          2.*Mp6[kk+2] +            //    2.*M_{k-1+0/6}
                                       mDn26*Mp6[kk+3] +            // mDn26*M_{k-1+2/6}
                                       Kcp*( mD26*Mp6[kk+0] +       //  mD26*M_{k-1-4/6}
                                                  Mp6[kk+1] +       //       M_{k-1-2/6}
                                            mDn26*Mp6[kk+2] +       // mDn26*M_{k-1+0/6}
                                            mDn46*Mp6[kk+3] ) );    // mDn46*M_{k-1+2/6}

        //------ free molecular

        const double Kfm = coag->getKfm(state);

        for (size_t k=1; k<Nmom; k++)                   // skip moment 0 (no growth term)
            Mcnd_FM[k] = double(k)*Kfm*nDimer*mDimer*g_grid(k);

        //------ harmonic mean

        for (size_t k=1; k<Nmom; k++)                   // skip moment 0 (no growth term)
            Mcnd[k] = Mcnd_FM[k]*Mcnd_C[k] / (Mcnd_FM[k]+Mcnd_C[k]);
    }

    //---------- growth terms

    vector<double> Mgrw(Nmom, 0);
    const double Acoef = M_PI * pow(6./(M_PI*rhoSoot), twothird);

    if (grow->mechType != growthMech::NONE)
        for (size_t k=1; k<Nmom; k++)
            Mgrw[k] = Kgrw*Acoef*k*Mr(k-onethird);

    //---------- oxidation terms

    vector<double> Moxi(Nmom, 0);

    if (oxid->mechType != oxidationMech::NONE)
        for (size_t k=1; k<Nmom; k++)
            Moxi[k] = -Koxi*Acoef*k*Mr(k-onethird);

    //---------- coagulation terms

    vector<double> Mcoa(Nmom, 0);

    if (coag->mechType != coagulationMech::NONE)
        Mcoa = MOMICCoagulationRates(state, Mtemp);

    //---------- combine to make soot source terms

    for (size_t i=0; i<Nmom; i++)
        sources.sootSources[i] = Mnuc[i] + Mcnd[i] + Mgrw[i] + Moxi[i] + Mcoa[i];

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
/// Reduces the number of moments if needed to avoid invalid inversion.
///
/// @param M \input vector of moment values
///
////////////////////////////////////////////////////////////////////////////////

void sootModel_MOMIC::downselectIfNeeded(vector<double> &M) {

    //----------- lognormal distribution constants

    const double sigL = 3.0;
    const double mavg = 1.0E-21;

     if (M[0] <= 0)
		return;

    if (M[1] <= 0.0)
        M[1] = M[0] * mavg * exp(0.5 * pow(sigL,2.0));     // estimate an M1 value based on M0 and lognormal distribution

    if (M[2] <= 0.0)
        M[2] = M[0] * pow(mavg,2) * exp(0.5 * 4 * pow(sigL,2.0));     // estimate an M2 value based on M0 and lognormal distribution

    // CHECK: all remaining moments <= 0.0

	Nmom = M.size();
	bool zeros = false;

	do {
	    zeros = false;                   // reset flag
        for (size_t i=0; i<Nmom; i++)
            if (M[i] <= 0.0) {           // if value <= 0.0 found, throw flag and downselect by one
                zeros = true; 
                Nmom = Nmom - 1; 
            }

	} while (Nmom>3 && zeros);        // will not downselect below 3 moments

    M.resize(Nmom);

	return;
}

////////////////////////////////////////////////////////////////////////////////
/// 
/// Calculates the grid function described in Frenklach 2002 MOMIC paper
/// using polynomial interpolation between whole order moments.
/// 
/// @param  x     \input x grid point
/// @param  y     \input y grid point
/// @return f_{1/2}
/// 
/// \verbatim
/// Mq6: (-3 -1 1 3 5 7 9 11 13 15 17 19 21 23 25 27 29 31 33 35 37 39 41 43 45 47 49 51 53 55
/// indx:  0  1 2 3 4 5 6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29
/// f_l^(x,y) is composed of M_(x+7/6)*M_(y+3/6), etc. where fractions vary
///      All M_(frac) are in Mq6. All frac are odd sixth fractions. 
///      If x = 1, then, e.g., x+7/6 --> (6+7)/6=13/6; index 7/6 is 5, shift by 3 --> 13/6 is ind 8
///      If x = 2, then shift by 6; x = 3, then shift by 9, etc.
/// \endverbatim
/// 
////////////////////////////////////////////////////////////////////////////////

double sootModel_MOMIC::f_grid(int x, int y) {

    int xi = x*3;       // add this index
    int yi = y*3;       // add this index

    double f0, f1, f2, f3;

    //----------- 

    if (x==y) {                                      // exploit the symmetry
        f0 = 2.*(       Mq6[xi+0]  * Mq6[yi+2] +
                        Mq6[xi+1]  * Mq6[yi+1] );

        f1 = 2.*(       Mq6[xi+0]  * Mq6[yi+5] +  
                     2.*Mq6[xi+1]  * Mq6[yi+4] +
                        Mq6[xi+2]  * Mq6[yi+3] );

        if (y<=3)
            f2 = 2.*(   Mq6[xi+0]  * Mq6[yi+8] +  
                     2.*Mq6[xi+1]  * Mq6[yi+7] +
                        Mq6[xi+2]  * Mq6[yi+6] +
                     2.*Mq6[xi+3]  * Mq6[yi+5] +
                     2.*Mq6[xi+4]  * Mq6[yi+4] );

        if (y<=2)
            f3 = 2.*(   Mq6[xi+0]  * Mq6[yi+11] +  
                     2.*Mq6[xi+1]  * Mq6[yi+10] +
                        Mq6[xi+2]  * Mq6[yi+9]  +
                     3.*Mq6[xi+3]  * Mq6[yi+8]  +
                     6.*Mq6[xi+4]  * Mq6[yi+7]  +
                     3.*Mq6[xi+5]  * Mq6[yi+6] );
    }
    else {

        f0 =            Mq6[xi+0]  * Mq6[yi+2] +     // note the pattern (0, 1, 2; 2, 1, 0)
                     2.*Mq6[xi+1]  * Mq6[yi+1] + 
                        Mq6[xi+2]  * Mq6[yi+0];

        f1 =            Mq6[xi+0]  * Mq6[yi+5] +  
                     2.*Mq6[xi+1]  * Mq6[yi+4] +
                        Mq6[xi+2]  * Mq6[yi+3] +
                        Mq6[xi+3]  * Mq6[yi+2] +
                     2.*Mq6[xi+4]  * Mq6[yi+1] +
                        Mq6[xi+5]  * Mq6[yi+0] ;

        if (y<=3)    
            f2 =        Mq6[xi+0]  * Mq6[yi+8] +  
                     2.*Mq6[xi+1]  * Mq6[yi+7] +
                        Mq6[xi+2]  * Mq6[yi+6] +
                     2.*Mq6[xi+3]  * Mq6[yi+5] +
                     4.*Mq6[xi+4]  * Mq6[yi+4] +
                     2.*Mq6[xi+5]  * Mq6[yi+3] +
                        Mq6[xi+6]  * Mq6[yi+2] +
                     2.*Mq6[xi+7]  * Mq6[yi+1] +
                        Mq6[xi+8]  * Mq6[yi+0] ;

        if (y<=2)    
            f3 =        Mq6[xi+0]  * Mq6[yi+11] +  
                     2.*Mq6[xi+1]  * Mq6[yi+10] +
                        Mq6[xi+2]  * Mq6[yi+9]  +
                     3.*Mq6[xi+3]  * Mq6[yi+8]  +
                     6.*Mq6[xi+4]  * Mq6[yi+7]  +
                     3.*Mq6[xi+5]  * Mq6[yi+6]  +
                     3.*Mq6[xi+6]  * Mq6[yi+5]  +
                     6.*Mq6[xi+7]  * Mq6[yi+4]  +
                     3.*Mq6[xi+8]  * Mq6[yi+3]  +
                        Mq6[xi+9]  * Mq6[yi+2]  +
                     2.*Mq6[xi+10] * Mq6[yi+1]  +
                        Mq6[xi+11] * Mq6[yi+0]  ;
    }

    //----------- Lagrange interpolation to point 1/2 using some or all of points 0, 1, 2, 3

    double fhalf;
    if (y<=2)       // 4 point interpolant
        fhalf = pow(f0,5./16.) * pow(f1,15./16.) * pow(f2, -5./16.) * pow(f3, 1./16.);
    else if (y<=3)  // 3 point interpolant
        fhalf = pow(f0, 3./8.) * pow(f1,  3./4.) * pow(f2,  -1./8.);
    else            // h point interpolant
        fhalf = pow(f0, 1./2.) * pow(f1,  1./2.);

    return fhalf;
}

////////////////////////////////////////////////////////////////////////////////
///
/// Calculates the grid function described in Frenklach 2002 MOMIC paper
/// using polynomial interpolation between whole order moments
/// 
/// @param y   \input y grid point
/// @return g_grid value.
///
/// Assumes mDn36, etc. (mDimer^powers) have been set in set_mDimerPowers()
/// 
/// \verbatim
/// Mq6: (-3 -1 1 3 5 7 9 11 13 15 17 19 21 23 25 27 29 31 33 35 37 39 41 43 45 47 49 51 53 55
/// indx:  0  1 2 3 4 5 6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29
/// f_l^(x,y) is composed of M_(x+7/6)*M_(y+3/6), etc. where fractions vary
///      All M_(frac) are in Mq6. All frac are odd sixth fractions. 
///      If x = 1, then, e.g., x+7/6 --> (6+7)/6=13/6; index 7/6 is 5, shift by 3 --> 13/6 is ind 8
///      If x = 2, then shift by 6; x = 3, then shift by 9, etc.
/// \end verbatim
///
////////////////////////////////////////////////////////////////////////////////

double sootModel_MOMIC::g_grid(int y) {

    int yi = (y-1)*3;       // add this index

    double g0, g1, g2, g3;

    set_mDimerPowers();  // fixes issue in simple_example of different output with each run jansenpb
    //----------- 

    g0 =            mD16   * Mq6[yi+0] +
                 2.*mDn16  * Mq6[yi+1] + 
                    mDn36  * Mq6[yi+2];

    g1 =            mD76   * Mq6[yi+0] +  
                 2.*mD56   * Mq6[yi+1] +
                    mD36   * Mq6[yi+2] +
                    mD16   * Mq6[yi+3] +
                 2.*mDn16  * Mq6[yi+4] +
                    mDn36  * Mq6[yi+5] ;

    if (y<=3)    
        g2 =        mD136  * Mq6[yi+0] +  
                 2.*mD116  * Mq6[yi+1] +
                    mD96   * Mq6[yi+2] +
                 2.*mD76   * Mq6[yi+3] +
                 4.*mD56   * Mq6[yi+4] +
                 2.*mD36   * Mq6[yi+5] +
                    mD16   * Mq6[yi+6] +
                 2.*mDn16  * Mq6[yi+7] +
                    mDn36  * Mq6[yi+8] ;

    if (y<=2)    
        g3 =        mD196 * Mq6[yi+0] +  
                 2.*mD176 * Mq6[yi+1] +
                    mD156 * Mq6[yi+2]  +
                 3.*mD136 * Mq6[yi+3]  +
                 6.*mD116 * Mq6[yi+4]  +
                 3.*mD96  * Mq6[yi+5]  +
                 3.*mD76  * Mq6[yi+6]  +
                 6.*mD56  * Mq6[yi+7]  +
                 3.*mD36  * Mq6[yi+8]  +
                    mD16  * Mq6[yi+9]  +
                 2.*mDn16 * Mq6[yi+10]  +
                    mDn36 * Mq6[yi+11]  ;

    //----------- Lagrange interpolation to point 1/2 using some or all of points 0, 1, 2, 3

    double ghalf;
    if (y<=2)       // 4 point interpolant
        ghalf = pow(g0,5./16.) * pow(g1,15./16.) * pow(g2, -5./16.) * pow(g3, 1./16.);
    else if (y<=3)  // 3 point interpolant
        ghalf = pow(g0, 3./8.) * pow(g1,  3./4.) * pow(g2,  -1./8.);
    else            // h point interpolant
        ghalf = pow(g0, 1./2.) * pow(g1,  1./2.);

    return ghalf;
}

////////////////////////////////////////////////////////////////////////////////
///
/// Get coagulation rates for moment k
/// 
/// @param state \input        gas and soot state, set by user.
/// @param M     \input        vector of soot moments
/// @return vector of coagulation rates
///
////////////////////////////////////////////////////////////////////////////////

vector<double> sootModel_MOMIC::MOMICCoagulationRates(const state& state, vector<double>& M){

    if (M[0] <= 0.0) return vector<double>(Nmom, 0.0);

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
                Rates_FM[r] = -0.5*Kfm*f_grid(0,0);
            else {
                for (size_t k=1; k<=r-1; k++)
                    Rates_FM[r] += binomial_coefficient(r,k) * f_grid(k, r-k);
                Rates_FM[r] *= 0.5*Kfm;
            }
        }
    }

    //----------- continuum regime

    if (coag->mechType == coagulationMech::CONTINUUM || 
             coag->mechType == coagulationMech::HM) {

        const double Kc  = coag->getKc( state);
        const double Kcp = coag->getKcp(state);


        for (size_t r=0; r<Nmom; r++) {
            if (r==1) continue; 
            if (r==0)
                Rates_C[r] = -Kc*( Mp6[2]*Mp6[2] + Mp6[1]*Mp6[3] +            // M_0*M_0 + M_{-2/6}*M_{2/6}
                                   Kcp*( Mp6[1]*Mp6[2] + Mp6[0]*Mp6[3] ) );   // M_{-2/6}*M_0 + M_{-4/6}*M_{2/6}
            else {
                size_t kk, rk;        // index shifters
                for (size_t k=1; k<=r-1; k++) {
                    kk = k*3;
                    rk = (r-k)*3;
                    Rates_C[r] = binomial_coefficient(r,k) * (
                                       Mp6[kk+1]*Mp6[rk+3] +                  // M_{k-2/6}*M_{r-k+2/6}
                                 2.0*  Mp6[kk+2]*Mp6[rk+2] +                  // M_{k+0/6}*M_{r-k+0/6}
                                       Mp6[kk+3]*Mp6[rk+1] +                  // M_{k+2/6}*M_{r-k-2/6}
                                 Kcp*( Mp6[kk+0]*Mp6[rk+3] +                  // M_{k-4/6}*M_{r-k+2/6}
                                       Mp6[kk+1]*Mp6[rk+2] +                  // M_{k-2/6}*M_{r-k+0/6}
                                       Mp6[kk+2]*Mp6[rk+1] +                  // M_{k+0/6}*M_{r-k-2/6}
                                       Mp6[kk+3]*Mp6[rk+0] ) );               // M_{k+2/6}*M_{r-k-4/6}
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
        else      // harmonic mean
            Rates[r] = Rates_FM[r]*Rates_C[r] / (Rates_FM[r]+Rates_C[r]);
    }

    return Rates;
}

////////////////////////////////////////////////////////////////////////////////
///
/// Compute PAH condensation terms for MOMIC model.
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

double sootModel_MOMIC::pahSootCollisionRatePerDimer(const state &state, const double mDimer) {

    if (nucl->mechType != nucleationMech::PAH)
        return 0.0;

    set_mDimerPowers();

    //------ continuum

    const double Kc  = coag->getKc( state);
    const double Kcp = coag->getKcp(state);

    double Ic1 = Kc * (  
                  mD26*Mp6[1] +            //  mD26*M_{-2/6}
                    2.*Mp6[2] +            //    2.*M_{ 0/6}
                 mDn26*Mp6[3] +            // mDn26*M_{ 2/6}
                 Kcp*( mD26*Mp6[0] +       //  mD26*M_{-4/6}
                            Mp6[1] +       //       M_{-2/6}
                      mDn26*Mp6[2] +       // mDn26*M_{ 0/6}
                      mDn46*Mp6[3] ) );    // mDn46*M_{ 2/6}

    //------ free molecular

    const double Kfm = coag->getKfm(state);

    double Ifm1 = Kfm*g_grid(1);

    //------ harmonic mean

    return Ifm1*Ic1/(Ifm1 + Ic1);
}

///////////////////////////////////////////////////////////////////////////////
/// 
/// Compute the difference table for a Newton polynomial.
/// \verbatim
/// x points are 0,   1,  2,  3, ... (hard-coded this way).
/// y points are M0, M1, M2, M3, ... (or log10 of those, or whatever is passed to l10M)
/// M0 dM0=M1-M0 ddM0=dM1-dM0 dddM0=ddM1-ddM0
/// M1 dM1=M2-M1 ddM1=dM2-dM1
/// M2 dM2=M3-M2           
/// M3
/// \endverbatim
/// (Interpolating among log10(M) here; nomenclature in code reflects that
///  but there is no change other than the var names.)
/// 
/// Function used by get_Mr.
/// Function only needs to be set when the set of moments change, so call once
///   at the top of the rates routine.
/// Code verified by comparison to np.polyfit, np.polyval.
///
/// @param M \input vector of Moments, converted to log10(Moments).
///
////////////////////////////////////////////////////////////////////////////////

void sootModel_MOMIC::set_diffTable(const vector<double> &M) {

    //----------- set first column

    for (int k=0; k<Nmom; k++)
        diffTable[k][0] = log10(M[k]);

    //----------- set other columns (differences) using previous column

    for (int j=1; j<Nmom; j++)           // each column
        for (int i=0; i<Nmom-j; i++)     // elements in column (row values)
            diffTable[i][j] = diffTable[i+1][j-1] - diffTable[i][j-1];
}

////////////////////////////////////////////////////////////////////////////////
///
/// Compute fractional moment r by Newton forward polynomial.
/// \verbatim
/// x points are 0,   1,  2,  3, ... (hard-coded this way)
/// y points are M0, M1, M2, M3, ... (log10 of those, or what is set in set_diffTable)
///     but returned value is 10^l10Mr here.
/// \endverbatim
/// Assumes diffTable is set.
/// Mr = M0 + r*dM0 + r(r-1)*ddM0/2!+ r(r-1)(r-2)*dddM0/3! + ...
/// Positive and negative moments get different treatement.
///    Positive interpolates among all moments.
///    Negative extrapolates from M0, M1, M2 (log of those).
/// Code verified by comparison to np.polyfit, np.polyval.
///
/// @param r \input fractional moment r
/// @return fractional moment Mr
/// 
////////////////////////////////////////////////////////////////////////////////

double sootModel_MOMIC::Mr(const double r) {

    double l10Mr = diffTable[0][0];
    double coef = r;
    int kend = (r >= 0) ? Nmom : 3;
    for(int k=1; k<kend; k++) {
        l10Mr += coef*diffTable[0][k];
        coef *= (r-k)/double(k+1);
    }

    double value = pow(10., l10Mr);
    return isfinite(value) ? value : 0.0;
}

////////////////////////////////////////////////////////////////////////////////
///
/// Compute arrays of fractional moments.
/// Used to compute coagulation.
/// \verbatim
/// Mp6 = M_{p/6}          evens (Continuum)
///     Mp6 = (-4 -2 0 2 4 6 8 10 12 14 16 18 20 22 24 26 28 30 32 34 36 38) / 6
///     indx:   0  1 2 3 4 5 6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21
///     indx = (p+4)/2
/// Mq6 = M_{q/6}          odds (FM)
///     Mq6 = (-3 -1 1 3 5 7 9 11 13 15 17 19 21 23 25 27 29 31 33 35 37 39 41 43 45 47 49 51 53 55) / 6
///     indx:   0  1 2 3 4 5 6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29
///     indx = (q+3)/2
/// \endverbatim
///
////////////////////////////////////////////////////////////////////////////////

void sootModel_MOMIC::set_fractional_moments_Mp6_Mq6() {

    double p;
    for(size_t i=0, p=-4; i<np[Nmom]; i++, p+=2)
        Mp6[i] = Mr(p/6.0);

    double q;
    for(size_t i=0, q=-3; i<nq[Nmom]; i++, q+=2)
        Mq6[i] = Mr(q/6.0);

}

////////////////////////////////////////////////////////////////////////////////
///
/// Set powers of mDimer used in other routines.
///
////////////////////////////////////////////////////////////////////////////////

void sootModel_MOMIC::set_mDimerPowers() {

    double mDimer = nucl->DIMER.mDimer;

    mD26  = pow(mDimer,  2./6.);
    mDn26 = pow(mDimer, -2./6.);
    mDn46 = pow(mDimer, -4./6.);

    mDn36  = pow(mDimer,  -3./6.);
    mDn16  = pow(mDimer,  -1./6.);
    mD16   = pow(mDimer,   1./6.);
    mD36   = pow(mDimer,   3./6.);
    mD56   = pow(mDimer,   5./6.);
    mD76   = pow(mDimer,   7./6.);
    mD96   = pow(mDimer,   9./6.);
    mD116  = pow(mDimer,  11./6.);
    mD136  = pow(mDimer,  13./6.);
    mD156  = pow(mDimer,  15./6.);
    mD176  = pow(mDimer,  17./6.);
    mD196  = pow(mDimer,  19./6.);
}

