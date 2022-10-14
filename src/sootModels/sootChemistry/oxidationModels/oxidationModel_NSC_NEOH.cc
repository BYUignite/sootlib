#include "sootModels/sootChemistry/oxidationModels/oxidationModel_NSC_NEOH.h"
#include "sootDefs.h"

using namespace std;
using namespace soot;

oxidationModel_NSC_NEOH::oxidationModel_NSC_NEOH() {

    oxidationRxnRatios[gasSp::CO] =  2;
    oxidationRxnRatios[gasSp::H] =   1;
    oxidationRxnRatios[gasSp::OH] = -1;
    oxidationRxnRatios[gasSp::O2] = -0.5;
    oxidationRxnRatios[gasSp::C]  = -2;

    mechType = oxidationMech::NSC_NEOH;
}

double oxidationModel_NSC_NEOH::getOxidationSootRate(const state &state) const {

    double pO2_atm = state.getGasSpP(gasSp::O2) / 101325.0; // partial pressure of O2 (atm)
    double pOH_atm = state.getGasSpP(gasSp::OH) / 101325.0; // partial pressure of OH (atm)

    double kA = 20 * exp(-15098 / state.T);              // rate constants
    double kB = 4.46E-3 * exp(-7650 / state.T);
    double kT = 1.51E5 * exp(-48817 / state.T);
    double kz = 21.3 * exp(2063 / state.T);

    double x = 1 / (1 + kT / (kB * pO2_atm));                    // x = unitless fraction
    double NSC_rate = kA * pO2_atm * x / (1 + kz * pO2_atm) + kB * pO2_atm * (1.0 - x);   // kmol/m^2*s
    double rSootO2 = NSC_rate * rhoSoot;                   // kg/m2*s
    double rSootOH = 1290 * 0.13 * pOH_atm / sqrt(state.T);    // kg/m2*s

    return rSootO2 + rSootOH;                                               // kg/m2*s
}
