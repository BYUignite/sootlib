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
/** Nucleation and condensation via PAH based on Blanquart and Pitsch in Bockhorn 
 *  Combustion Generated Fine Carbonaceous Particles, Chapter 27, 2009.
 *  PAH   + PAH   --> Dimer 
 *  Dimer + Dimer --> (soot nucleation) + (condensation)
 *  sum_i gamma_i*beta_i,i*[pah_i]*[pah_i] = 2*beta_DD*[D][D] + (sum_i beta_Si,D*[w_i])[D]
 *                ndot_D                   =    ndot_D,Nuc    +       ndot_D,cond
 *  here, [] denotes #/m3; In Blanquart and Pitsch ndot_D is denoted omega.
 *
 *  mdot_pah_i = -2*(gamma_i*beta_i,i*[pah_i]*[pah_i])*m_pah_i
 *  This mdot_pah_i goes into soot as C with H coming off as H2
 *  mdot_pah_i = variable nucleationPahRxnRates and accounts for nucleation and condensation.
 */

double nucleationModel_PAH::getNucleationSootRate(state& state) {

    double nDotD  = 0.0;                 // dimer self collision (formation) rate: #/m3*s
    double mDimer = 0.0;                 // reset dimer mass (kg/part)
    double nDimer = 0.0;                 // reset dimer number density
    double cMin   = state.cMin;          // min number of carbon atoms in a soot particle
    double hMin   = 0.0;

    //------------ compute the dimer self collision rate nDotD and mass mDimer (kg/particle)

    static double preFac = 4.0*sqrt(M_PI*kb*state.T)*pow(6./(M_PI*rhoSoot), twothird);  // Blanquart and Pitsch have the 4 in the sqrt

    //-----------  loop over PAH species

    for (int sp=0; sp<(int)pahSp::size; sp++) {

        double Ni    = state.rhoGas * state.yPah[sp] / pahSpMW[sp] * Na;            // #/m3 for given pah species
        double ndoti = pahSpGamma[sp]*preFac*pow(pahSpMW[sp]/Na, 1.0/6.0)*Ni*Ni;    // collisions_i/(m3*s) = #_Dimers/m3*s = 0.5#pah_i/m3*s

        nDotD  += ndoti;
        mDimer += ndoti * 2.0*pahSpNC[sp]*gasSpMW[(int)gasSp::C]/Na;  // normalized by nDotD below
        cMin   += ndoti * 4.0*pahSpNC[sp];                            // normalized below; *4: (pah+pah)+(pah+pah)=(dimer)+(dimer) = soot nuc
        hMin   += ndoti * 4.0*pahSpNH[sp];                            // normalized below; *4: (pah+pah)+(pah+pah)=(dimer)+(dimer) = soot nuc

        nucleationPahRxnRates[sp] = -2.0*ndoti*pahSpMW[sp]/Na;        // PAH gas sources; kg/m3*s;
    }

    if (nDotD > 0) {
        mDimer /= nDotD;      // normalize
        cMin   /= nDotD;      // normalize
        hMin   /= nDotD;      // normalize
    }
    state.cMin = cMin;        // cMin is reset here; some mechanisms have this as an input

    nucleationRxnRatios[(int)gasSp::C]  = 1.0;
    nucleationRxnRatios[(int)gasSp::H2] = hMin/2.0/cMin;

    //----------- compute the dimer concentration as solution to quadratic
    // Steady state approximation.
    // Dimer creation rate = dimer destruction from self collision + from soot collision (condensation)
    // nDotD = 2*beta_DD*[D]^2 + sum(beta_DS*w_i)*[D]

    double beta_DD = preFac*pow(mDimer, 1.0/6.0);   // dimer self-collision rate coefficient

    double I_beta_DS = 0.0;                         // sum of dimer-soot collision rates
    if (SM->psdMechType == psdMech::LOGN)
        I_beta_DS = SM->pahSootCollisionRatePerDimer(mDimer);
    else
        for (int i = 0; i < state.absc.size(); i++)     // loop over soot "particles" (abscissas)
            I_beta_DS += abs(state.wts[i]) * SM->coag->getCoagulationSootRate(state, mDimer, state.absc[i]);

    //----------- solve quadratic for D: beta_DD*(D^2) + I_beta_DS*(D) - nDotD = 0
    // See Numerical Recipes 3rd ed. Sec 5.6 page 227. (Choosing the positive root.)

    if (nDotD > 0 && mDimer > 0)     // nDimer initialized to 0 above
        nDimer = 2.0*nDotD/(I_beta_DS + sqrt(I_beta_DS*I_beta_DS + 4.*2.*beta_DD*nDotD));   // #/m3

    //----------- populate DIMER structure with updated values

    DIMER.mDimer = mDimer;
    DIMER.nDimer = nDimer;
    DIMER.nDotD  = nDotD;

    //----------- return nucleation rate Jnuc (=) #/m3*s, (#nucleated particles/m3*s)

    return beta_DD*nDimer*nDimer;
}
