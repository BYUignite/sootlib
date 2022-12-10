#include "oxidationModels/oxidationModel_LEE_NEOH.h"
#include "sootDefs.h"

using namespace soot;

////////////////////////////////////////////////////////////////////////////////

oxidationModel_LEE_NEOH::oxidationModel_LEE_NEOH() {

    // C + OH      --> CO + H   
    //                          --> 2C_soot + OH + (1/2)O2 --> 2CO + H
    // C + (1/2)O2 --> CO 

    oxidationRxnRatios[(int)gasSp::CO] =  2;
    oxidationRxnRatios[(int)gasSp::H] =   1;
    oxidationRxnRatios[(int)gasSp::OH] = -1;
    oxidationRxnRatios[(int)gasSp::O2] = -0.5;
    oxidationRxnRatios[(int)gasSp::C]  = -2;

    mechType = oxidationMech::LEE_NEOH;
}

////////////////////////////////////////////////////////////////////////////////
///
/// Oxidation by Lee et al. + Neoh
///
/// Rates from Lee et al. (1962) Comb. & Flame 6:137-145 and Neoh (1981)
/// "Soot oxidation in flames" in Particulate Carbon Formation During
/// Combustion book
/// C + 0.5 O2 --> CO
/// C + OH     --> CO + H
///
/// @param state \input  gas and soot state, set by user.
/// @return soot oxidation rate (kg/m2*s)
///
////////////////////////////////////////////////////////////////////////////////

double oxidationModel_LEE_NEOH::getOxidationSootRate(const state &state) const {

    const double pO2_atm = state.getGasSpP(gasSp::O2) / 101325.0;     // partial pressure of O2 (atm)

    const double rSootO2 = 1.085E4 * pO2_atm / sqrt(state.T) * exp(-1.977824E4 / state.T) / 1000.0;     // kg/m^2*s
    const double rSootOH = 0.13*state.getGasSpC(gasSp::OH)*       // kg/m2/s     = 1290*0.13*POH/sqrt(T) with POH in atm
                           sqrt(Rg*state.T/(2.0*M_PI*gasSpMW[(int)gasSp::OH]))*
                           gasSpMW[(int)gasSp::C];

    return rSootO2 + rSootOH;
}
