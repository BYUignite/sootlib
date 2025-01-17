#include "oxidationModels/oxidationModel_AJ_RED.h"
#include "sootDefs.h"

using namespace std;
using namespace soot;

////////////////////////////////////////////////////////////////////////////////

oxidationModel_AJ_RED::oxidationModel_AJ_RED() {

    oxidationRxnRatios[(int)gasSp::CO] =  1;      // C(soot) + (1/2)O2 --> CO
    oxidationRxnRatios[(int)gasSp::O2] = -0.5;
    oxidationRxnRatios[(int)gasSp::C]  = -1;

    mechType = oxidationMech::AJ_RED;
}

////////////////////////////////////////////////////////////////////////////////
///
/// Oxidation by Alex Josephson (2020) Only for use with growthHACA and when using tars 
///
/// Rate from Alex Josephson (2020) Reduction of a detailed soot model for simulations of pyrolysing solid fuels
/// Returns chemical soot oxidation rate in kg/m2*s.
///
/// C + 0.5 O2 --> CO
///
/// @param state \input  gas and soot state, set by user.
/// @return soot oxidation rate (kg/m2*s)
///
////////////////////////////////////////////////////////////////////////////////

double oxidationModel_AJ_RED::getOxidationSootRate(const state &state) const {

    return 1/sqrt(state.T) * (1.92E-3*state.getGasSpP(gasSp::O2)*exp(-1.16E5/(Rg*state.T)) + 2.93E-3*state.getGasSpP(gasSp::OH));    //

}
