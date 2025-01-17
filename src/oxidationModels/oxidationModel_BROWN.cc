#include "oxidationModels/oxidationModel_BROWN.h"
#include "sootDefs.h"

using namespace std;
using namespace soot;

///////////////////////////////////////////////////////////////////////////

oxidationModel_BROWN::oxidationModel_BROWN() {

    oxidationRxnRatios[(int)gasSp::CO] =  1;
    oxidationRxnRatios[(int)gasSp::O2] = -0.5;
    oxidationRxnRatios[(int)gasSp::C]  = -1;

    mechType = oxidationMech::BROWN;
}

///////////////////////////////////////////////////////////////////////////
///
/// Oxidation by Brown and Fletcher 1998 (revised by Josephson and Lignell 2016)
/// 
/// @param state \input gas, soot, and tar state, set by user
/// @return soot oxidation rate (kg/m2*s)
///
///////////////////////////////////////////////////////////////////////////

double oxidationModel_BROWN::getOxidationSootRate(const state &state) const {

    double A_OC = 1.09E5/101325; //> kg*K^(1/2)/m2*Pa*s
    double E_OC = 1.645E8;       //> J/kmol

    return state.getGasSpP(gasSp::O2) / sqrt(state.T) * A_OC * exp(-E_OC/(Rg*state.T)); // kg/m2*s 
}
