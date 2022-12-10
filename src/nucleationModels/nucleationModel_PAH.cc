#include "nucleationModels/nucleationModel_PAH.h"
#include "sootDefs.h"
#include "sootModel.h"

using namespace std;
using namespace soot;

////////////////////////////////////////////////////////////////////////////////

nucleationModel_PAH::nucleationModel_PAH() : nucleationModel () {

    DIMER.mDimer = 0;
    DIMER.nDimer = 0;
    DIMER.nDotD  = 0;

    mechType = nucleationMech::PAH;
}

////////////////////////////////////////////////////////////////////////////////
///
/// Rate from Blanquart & Pitsch (2009) article "A joint
/// volume-surface-hydrogen multi-variate model for soot formation," ch. 27
/// in Combustion Generated Fine Carbonaceous Particles ed. Bockhorn et al.
/// PAH   + PAH   --> Dimer 
/// Dimer + Dimer --> (soot nucleation) + (condensation)
/// 
/// nDoti = dn_PAHi/dt = gamma_i*beta_i,i * n_PAH_i^2       (ignoring the neg sign here)
/// 
/// nDotD = dn_D/dt    = sum_i( 0.5*nDoti )                 half as many dimers formed as pah lost
///
/// mDimer = sum_i( nDoti*m_PAHi ) / sum_i( nDoti )
///        = sum_i( nDoti*m_PAHi ) / (2*nDotD)
///
///
/// Assume dimers are in steady state. Use to solve for nD (quadratic equation)
///
/// beta_DD*(nD)^2             + (sum_i beta_D,s_i * n_si)*(nD)        - nDotD           = 0
/// (kill by soot nuc from D)  + (kill by dimer condensation on soot)  - (form by PAH)   = 0
///
/// PAH --> D --> soot as C, with H coming off as H2
///
/// @param state \input  gas and soot state, set by user.
/// @return soot nucleation rate (\#/m3*s)
///
////////////////////////////////////////////////////////////////////////////////

double nucleationModel_PAH::getNucleationSootRate(state& state) {

    double nDotD  = 0.0;                 // dimer self collision (formation) rate: #/m3*s
    double mDimer = 0.0;                 // reset dimer mass (kg/part)
    double nDimer = 0.0;                 // reset dimer number density
    double cMin   = state.cMin;          // min number of carbon atoms in a soot particle
    double hMin   = 0.0;

    //------------ compute the dimer self collision rate nDotD and mass mDimer (kg/particle)

    static double preFac = 4.0*sqrt(M_PI*kb*state.T)*pow(6./(M_PI*rhoSoot), twothird);

    //-----  loop over PAH species

    for (int sp=0; sp<(int)pahSp::size; sp++) {

        double Ni    = state.rhoGas * state.yPah[sp] / pahSpMW[sp] * Na;            // #/m3 for given pah species
        double ndoti = pahSpGamma[sp]*preFac*pow(pahSpMW[sp]/Na, 1.0/6.0)*Ni*Ni;    // dn_pahi/dt

        nDotD  += 0.5*ndoti;                                          // dn_Dimer/dt
        mDimer += ndoti *     pahSpNC[sp]*gasSpMW[(int)gasSp::C]/Na;  // normalized by nDotD below
        cMin   += ndoti * 2.0*pahSpNC[sp];                            // normalized below; *2: two dimers make one nucleated soot particle
        hMin   += ndoti * 2.0*pahSpNH[sp];                            // normalized below; *2: two dimers make one nucleated soot particle

        nucleationPahRxnRates[sp] = -ndoti*pahSpMW[sp]/Na;            // PAH gas sources; kg/m3*s;
    }

    if (nDotD > 0) {
        mDimer /= 2.0*nDotD;      // normalize
        cMin   /= 2.0*nDotD;      // normalize
        hMin   /= 2.0*nDotD;      // normalize
    }
    state.cMin = cMin;            // cMin is reset here; some mechanisms have this as an input

    nucleationRxnRatios[(int)gasSp::C]  = 1.0;
    nucleationRxnRatios[(int)gasSp::H2] = hMin/2.0/cMin;

    //----------- compute the dimer concentration nDimer as solution to quadratic
    //----------- NOTE: this must be consistent with sootModel_XXXX::getSourceTerms func for condensation

    double beta_DD = preFac*pow(mDimer, 1.0/6.0);       // dimer self-collision rate coefficient

    double I_beta_DS = 0.0;                             // sum of dimer-soot collision rates
    if (SM->psdMechType == psdMech::LOGN  || 
        SM->psdMechType == psdMech::MOMIC || 
        SM->psdMechType == psdMech::SECT )
        I_beta_DS = SM->pahSootCollisionRatePerDimer(mDimer);
    else
        for (int i = 0; i < state.absc.size(); i++)     // loop over soot "particles" (abscissas)
            I_beta_DS += abs(state.wts[i]) * SM->coag->getCoagulationSootRate(state, mDimer, state.absc[i]);

    //------ solve quadratic for D: beta_DD*(D^2) + I_beta_DS*(D) - nDotD = 0
    // See Numerical Recipes 3rd ed. Sec 5.6 page 227:
    // ax^2 + bx + c = 0; q=-0.5*(b+sgn(b)*sqrt(b*b-4*a*c)); x1=q/a; x2=c/q; Choose x2 as the + root

    if (nDotD > 0 && mDimer > 0)     // nDimer initialized to 0 above
        nDimer = 2.0*nDotD/(I_beta_DS + sqrt(I_beta_DS*I_beta_DS + 4.*beta_DD*nDotD));   // #/m3

    //----------- populate DIMER structure with updated values

    DIMER.mDimer = mDimer;
    DIMER.nDimer = nDimer;
    DIMER.nDotD  = nDotD;

    //----------- return nucleation rate Jnuc (=) #/m3*s, (#nucleated particles/m3*s)

    return 0.5*beta_DD*nDimer*nDimer;
}
