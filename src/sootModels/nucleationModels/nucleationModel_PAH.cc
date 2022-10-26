#include "sootModels/sootChemistry/nucleationModels/nucleationModel_PAH.h"
#include "sootDefs.h"

using namespace std;
using namespace soot;

////////////////////////////////////////////////////////////////////////////////

nucleationModel_PAH::nucleationModel_PAH() : nucleationModel () {

    DIMER.mDimer = 0;
    DIMER.nDimer = 0;
    DIMER.wDotD  = 0;

    mechType = nucleationMech::PAH;
}

////////////////////////////////////////////////////////////////////////////////

double nucleationModel_PAH::getNucleationSootRate(state& state) {

    // working variables (local)
    double wDotD  = 0.0;                 // dimer self collision (formation) rate: #/m3*s
    double mDimer = 0.0;                 // reset dimer mass (kg/part)
    double nDimer = 0.0;                 // reset dimer number density
    double cMin_local = state.cMin;      // min number of carbon atoms in a soot particle

    //------------ compute the dimer self collision rate wDotD and mass mDimer (kg/particle)

    double preFac = sqrt(4*M_PI*kb*state.T) * pow(6/(M_PI*rhoSoot), 2.0/3.0);

    // loop over PAH species list
    for (int sp=0; sp<(int)pahSp::size; sp++) {

        double Ni    = state.rhoGas * state.yPah[sp] / pahSpMW[sp] * Na;                          // species number density (#/m3)
        double wdoti = pahSpGamma[sp] * preFac * pow(pahSpMW[sp]/Na, 1.0/6.0) * Ni * Ni;    // convenience variable

        wDotD      += wdoti;
        mDimer     += wdoti * pahSpMW[sp]/Na;
        cMin_local += wdoti * pahSpNC[sp];

        // begin updating PAH reaction ratios
        nucleationPahRxnRates[sp] = wdoti * pahSpMW[sp] / Na;

    }

    if (mDimer > 0.0) {
        for (int sp=0; sp<(int)pahSp::size; sp++)
            nucleationPahRxnRates[sp] /= mDimer;   // now mdot_i_pah = pah_relative_rates[i]*mdot, where mdot is a total gas rate
    }

    if (wDotD > 0.0) {
        mDimer     *= wDotD > 0.0 ? 2.0 / wDotD : 0;
        cMin_local *= wDotD > 0.0 ? 4.0 / wDotD : 0;
    }

    state.cMin = cMin_local;            // cMin is reset here; some mechanisms have this as an input

    // finish updating PAH and gas species reaction ratios
    for (int sp=0; sp<(int)pahSp::size; sp++)
        nucleationPahRxnRates[sp] *= -2.0 * mDimer / (state.cMin * gasSpMW[(int)gasSp::C] / Na);

    if (mDimer != 0 && state.cMin != 0)
        nucleationRxnRatios[(int)gasSp::H2] = 2.0 * mDimer / (state.cMin * gasSpMW[(int)gasSp::C] / Na) - 1.0;

    //------------- compute the dimer concentration as solution to quadratic
    // Steady state approximation.
    // Dimer creation rate = dimer destruction from self collision + from soot collision
    // wDotD = beta_DD*[D]^2 + sum(beta_DS*w_i)*[D]

    double beta_DD = coagHM.getCoagulationSootRate(state, mDimer, mDimer);        // dimer self-collision rate
    double I_beta_DS = 0.0;                                                 // sum of dimer-soot collision rates
    for (int i = 0; i < state.absc.size(); i++)                                     // loop over soot "particles" (abscissas)
        I_beta_DS += abs(state.wts[i]) * coagHM.getCoagulationSootRate(state, mDimer, state.absc[i]);

    //------------- solve quadratic for D: beta_DD*(D^2) + I_beta_DS*(D) - wDotD = 0
    // See Numerical Recipes 3rd ed. Sec 5.6 page 227.
    // Choosing the positive root.

    if (wDotD == 0 || mDimer == 0)
        nDimer = 0;
    else
        nDimer = 2.0 * wDotD / (I_beta_DS + sqrt(I_beta_DS * I_beta_DS + 4 * beta_DD * wDotD));   // #/m3

    //------------- populate DIMER structure with updated values
    DIMER.mDimer = mDimer;
    DIMER.nDimer = nDimer;
    DIMER.wDotD  = wDotD;

    //------------- return nucleation rate Jnuc (=) #/m3*s
    return 0.5 * beta_DD * nDimer * nDimer;

}