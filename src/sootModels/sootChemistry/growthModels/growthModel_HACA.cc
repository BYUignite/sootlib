#include "sootModels/sootChemistry/growthModels/growthModel_HACA.h"
#include "sootDefs.h"

using namespace std;
using namespace soot;

growthModel_HACA::growthModel_HACA() {

    growthRxnRatios.at(gasSp::O2)   = -1;
    growthRxnRatios.at(gasSp::OH)   = -1;
    growthRxnRatios.at(gasSp::CO)   =  3;
    growthRxnRatios.at(gasSp::C)    =  2;

}

double growthModel_HACA::getGrowthSootRate(const state& state) const {

    double M0 = state.sootVar[0];                           // #/m3
    double M1 = state.sootVar[1];                           // kg/m3

    //---------- calculate alpha, other constants

    double RT = 1.9872036E-3 * state.T;            // R (=) kcal/mol
    double chi_soot = 2.3E15;                                 // (=) sites/cm^2
    double a_param = 33.167 - 0.0154 * state.T;         // a parameter for calculating alpha
    double b_param = -2.5786 + 0.00112 * state.T;       // b parameter for calculating alpha

    //---------- calculate raw HACA reaction rates

    double fR1 = 4.2E13 * exp(-13.0 / RT) * state.getGasSpC(gasSp::H) / 1000;
    double rR1 = 3.9E12 * exp(-11.0 / RT) * state.getGasSpC(gasSp::H2) / 1000;
    double fR2 = 1.0E10 * pow(state.T, 0.734) * exp(-1.43 / RT) * state.getGasSpC(gasSp::OH) / 1000;
    double rR2 = 3.68E8 * pow(state.T, 1.139) * exp(-17.1 / RT) * state.getGasSpC(gasSp::H2O) / 1000;
    double fR3 = 2.0E13 * state.getGasSpC(gasSp::H) / 1000;
    double fR4 = 8.00E7 * pow(state.T, 1.56) * exp(-3.8 / RT) * state.getGasSpC(gasSp::C2H2) / 1000;
    double fR5 = 2.2E12 * exp(-7.5 / RT) * state.getGasSpC(gasSp::O2) / 1000;
    double fR6 = 1290.0 * 0.13 * state.P * (state.getGasSpC(gasSp::OH) / state.rhoGas * gasSpMW.at(gasSp::OH)) / sqrt(state.T);    // gamma = 0.13 from Neoh et al.

    //---------- Steady state calculation of chi for soot radical; see Frenklach 1990 pg. 1561
    double denom = rR1 + rR2 + fR3 + fR4 + fR5;
    double chi_rad = denom == 0 ? 0 : 2 * chi_soot * (fR1 + fR2 + fR6) / denom;  // sites/cm^2

    double alpha = M0 > 0 ? tanh(a_param / log10(M1 / M0) + b_param) : 1;   // alpha = fraction of available surface sites
    if (alpha < 0) { alpha = 1; }

    double c_soot_H = alpha * chi_soot * 1E4;              // sites/m2-mixture
    double c_soot_rad = alpha * chi_rad * 1E4;              // sites/m2-mixture

    return (fR5 * c_soot_rad + fR6 * c_soot_H) / Na * 2 * gasSpMW.at(gasSp::C);    // kg/m2*s
}
