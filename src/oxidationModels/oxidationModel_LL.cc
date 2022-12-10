#include "oxidationModels/oxidationModel_LL.h"
#include "sootDefs.h"

using namespace std;
using namespace soot;

////////////////////////////////////////////////////////////////////////////////

oxidationModel_LL::oxidationModel_LL() {

    oxidationRxnRatios[(int)gasSp::CO] =  1;      // C(soot) + (1/2)O2 --> CO
    oxidationRxnRatios[(int)gasSp::O2] = -0.5;
    oxidationRxnRatios[(int)gasSp::C]  = -1;

    mechType = oxidationMech::LL;
}

////////////////////////////////////////////////////////////////////////////////
///
/// Oxidation by Leung_Lindstedt (1991)
///
/// Rate from Leung & Lindstedt (1991), Comb. & Flame 87:289-305.
/// Returns chemical soot oxidation rate in kg/m2*s.
///
/// C + 0.5 O2 --> CO
///
/// @param state \input  gas and soot state, set by user.
/// @return soot oxidation rate (kg/m2*s)
///
////////////////////////////////////////////////////////////////////////////////

double oxidationModel_LL::getOxidationSootRate(const state &state) const {

    return 0.1E5 * sqrt(state.T) * exp(-19680. / state.T) * 
           state.getGasSpC(gasSp::O2) * gasSpMW[(int)gasSp::C];    // kg_soot/m^2*s

}
