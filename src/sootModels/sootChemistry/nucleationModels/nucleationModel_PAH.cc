#include "nucleationModel_PAH.h"

using namespace std;
using namespace soot;

double nucleationModel_PAH::getNucleationSootRate(state& state, const vector<double> &mi, const vector<double> &wi) const {

    double wdotD  = 0.0;                // dimer self collision (formation) rate: #/m3*s
    double mDimer = 0.0;                // reset dimer mass (kg/part)
    double nDimer = 0.0;                // reset dimer number density
    double cMin_local = state.cMin;     // working copy of cMin

    //------------ compute the dimer self collision rate wdotD and mass mDimer (kg/particle)

    double preFac = sqrt(4*M_PI*kb*state.T)*pow(6/(M_PI*rhoSoot), 2.0/3.0);

    // loop over PAH species list
    for (auto const& x : *nucleationPahRxnRatios) {

        pahSp sp = x.first;

        double Ni    = state.rhoGas * state.pahFractions.at(sp) / pahSpMW.at(sp) * Na;                          // species number density (#/m3)
        double wdoti = abs(pahSpGamma.at(sp) * preFac * pow(pahSpMW.at(sp)/Na, 1.0/6.0) * Ni * Ni);    // convenience variable

        wdotD      += wdoti;
        mDimer     += wdoti * pahSpMW.at(sp)/Na;
        cMin_local += wdoti * pahSpNC.at(sp);

        // begin updating PAH reaction ratios
        nucleationPahRxnRatios->at(sp) = wdoti * pahSpMW.at(sp)/Na;

    }

    for (auto const& x : *nucleationPahRxnRatios)
        nucleationPahRxnRatios->at(x.first) /= mDimer;   // now mdot_i_pah = pah_relative_rates[i]*mdot, where mdot is a total gas rate

    mDimer     *= 2.0 / wdotD;
    cMin_local *= 4.0 / wdotD;

    state.cMin = cMin_local;            // cMin is reset here; some mechanisms have this as an input

    // finish updating PAH and gas species reaction ratios
    for (auto const& x : *nucleationPahRxnRatios)
        nucleationPahRxnRatios->at(x.first) *= -2.0 * mDimer / (state.cMin * gasSpMW.at(gasSp::C) / Na);

    nucleationRxnRatios->at(gasSp::H2) = 2.0 * mDimer / (state.cMin * gasSpMW.at(gasSp::C) / Na) - 1.0;

    //------------- compute the dimer concentration as solution to quadratic
    // Steady state approximation.
    // Dimer creation rate = dimer destruction from self collision + from soot collision
    // wdotD = beta_DD*[D]^2 + sum(beta_DS*w_i)*[D]

    double beta_DD = state.getParticleCollisionRate(mDimer, mDimer);        // dimer self-collision rate
    double I_beta_DS = 0.0;                                                 // sum of dimer-soot collision rates
    for (int i = 0; i < mi.size(); i++)                                     // loop over soot "particles" (abscissas)
        I_beta_DS += abs(wi[i]) * state.getParticleCollisionRate(mDimer, mi[i]);

    //------------- solve quadratic for D: beta_DD*(D^2) + I_beta_DS*(D) - wdotD = 0
    // See Numerical Recipes 3rd ed. Sec 5.6 page 227.
    // Choosing the positive root.

    nDimer = 2.0 * wdotD / (I_beta_DS + sqrt(I_beta_DS * I_beta_DS + 4 * beta_DD * wdotD));   // #/m3

    //------------- return nucleation rate Jnuc (=) #/m3*s
    return 0.5 * beta_DD * nDimer * nDimer;

}
