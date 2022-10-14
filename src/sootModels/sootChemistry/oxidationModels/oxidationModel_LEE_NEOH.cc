#include "sootModels/sootChemistry/oxidationModels/oxidationModel_LEE_NEOH.h"
#include "sootDefs.h"

using namespace soot;

oxidationModel_LEE_NEOH::oxidationModel_LEE_NEOH() {

    oxidationRxnRatios[gasSp::CO] =  2;
    oxidationRxnRatios[gasSp::H] =   1;
    oxidationRxnRatios[gasSp::OH] = -1;
    oxidationRxnRatios[gasSp::O2] = -0.5;
    oxidationRxnRatios[gasSp::C]  = -2;

    mechType = oxidationMech::LEE_NEOH;
}

double oxidationModel_LEE_NEOH::getOxidationSootRate(const state &state) const {

    const double pO2_atm = state.getGasSpP(gasSp::O2) / 101325.0;     // partial pressure of O2 (atm)
    const double pOH_atm = state.getGasSpP(gasSp::OH) / 101325.0;     // partial pressure of OH (atm)

    const double rSootO2 = 1.085E4 * pO2_atm / sqrt(state.T) * exp(-1.977824E4 / state.T) / 1000.0;     // kg/m^2*s
    const double rSootOH = 1290 * 0.13 * pOH_atm / sqrt(state.T);                                       // kg/m^2*s

    return rSootO2 + rSootOH;
}
