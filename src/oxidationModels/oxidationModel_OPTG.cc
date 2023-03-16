#include "oxidationModels/oxidationModel_OPTG.h"
#include "sootDefs.h"

using namespace soot;

////////////////////////////////////////////////////////////////////////////////

oxidationModel_OPTG::oxidationModel_OPTG() {

    // C + OH      --> CO + H   
    //                          --> 2C_soot + OH + (1/2)O2 --> 2CO + H
    // C + (1/2)O2 --> CO 

    oxidationRxnRatios[(int)gasSp::CO] =  2;
    oxidationRxnRatios[(int)gasSp::H] =   1;
    oxidationRxnRatios[(int)gasSp::OH] = -1;
    oxidationRxnRatios[(int)gasSp::O2] = -0.5;
    oxidationRxnRatios[(int)gasSp::C]  = -2;

    mechType = oxidationMech::OPTG;
}

////////////////////////////////////////////////////////////////////////////////
///
/// Oxidation by Guo et al. 2016
///
/// H. Guo, P.M. Anderson, P.B. Sunderland,
/// "Optimized rate expressions for soot oxidation by OH and O2," 
/// Fuel 172:248-252(2016). http://dx.doi.org/10.1016/j.fuel.2016.01.030
///
/// C + 0.5 O2 --> CO
/// C + OH     --> CO + H
///
/// @param state \input  gas and soot state, set by user.
/// @return soot oxidation rate (kg/m2*s)
///
////////////////////////////////////////////////////////////////////////////////

double oxidationModel_OPTG::getOxidationSootRate(const state &state) const {

    const double pO2_pa = state.getGasSpP(gasSp::O2);     // partial pressure of O2 (Pa)

    const double rSootO2 = 15.8 * pO2_pa / sqrt(state.T) * exp(-2.345E4 / state.T) / 1000.0;     // kg/m^2*s
    const double rSootOH = 0.1*state.getGasSpC(gasSp::OH)*       // kg/m2/s     = 1290*0.15*POH/sqrt(T) with POH in atm
                           sqrt(Rg*state.T/(2.0*M_PI*gasSpMW[(int)gasSp::OH]))*
                           gasSpMW[(int)gasSp::C];

    return rSootO2 + rSootOH;
}
