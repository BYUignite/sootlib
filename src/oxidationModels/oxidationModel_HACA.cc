#include "oxidationModels/oxidationModel_HACA.h"
#include "sootDefs.h"

using namespace std;
using namespace soot;

oxidationModel_HACA::oxidationModel_HACA() {

    oxidationRxnRatios[(int)gasSp::OH]   = -1;
    oxidationRxnRatios[(int)gasSp::CO]   =  1;
    oxidationRxnRatios[(int)gasSp::C]    = -1;

    mechType = oxidationMech::HACA;
}

double oxidationModel_HACA::getOxidationSootRate(const state &state) const {

    double M0 = state.sootVar[0];                           // #/m3
    double M1 = state.sootVar[1];                           // kg/m3

    //---------- calculate alpha, other constants
    double chi_soot = 2.3E15;                                 // (=) sites/cm^2
    double a_param = 33.167 - 0.0154 * state.T;         // a parameter for calculating alpha
    double b_param = -2.5786 + 0.00112 * state.T;       // b parameter for calculating alpha

    //---------- calculate raw HACA reaction rates
    // Oxidation by O2 is considered by the HACA growth model since its reaction is required for steady state calculation of radical site availability
    double fR6 = 1290 * 0.13 * state.P * (state.getGasSpC(gasSp::OH) / state.rhoGas * gasSpMW[(int)gasSp::OH]) / sqrt(state.T);    // gamma = 0.13 from Neoh et al.

    double alpha = M0 > 0 ? tanh(a_param / log10(M1 / M0) + b_param) : 1;   // alpha = fraction of available surface sites
    if (alpha < 0) { alpha = 1; }

    double c_soot = -fR6 * alpha * chi_soot * 10;         // sites/m2*s

    return c_soot / Na * gasSpMW[(int)gasSp::C];            // kg/m2*s

}
