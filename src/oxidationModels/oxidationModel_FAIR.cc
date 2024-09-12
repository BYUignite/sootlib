#include "oxidationModels/oxidationModel_FAIR.h"
#include "sootDefs.h"

using namespace std;
using namespace soot;

////////////////////////////////////////////////////////////////////////////////

oxidationModel_FAIR::oxidationModel_FAIR() {

    oxidationRxnRatios[(int)gasSp::CO] =  1;      // C(soot) + (1/2)O2 --> CO
    oxidationRxnRatios[(int)gasSp::O2] = -0.5;
    oxidationRxnRatios[(int)gasSp::C]  = -1;

    mechType = oxidationMech::LL;
}

////////////////////////////////////////////////////////////////////////////////
///
/// Oxidation by Fairweather (1992)
///
/// Rate from Predictions of Radiative Transfer from a Turbulent Reacting Jet in a Cross-Wind (1992)
/// Returns chemical soot oxidation rate in kg/m2*s.
///
/// C + 0.5 O2 --> CO
///
/// @param state \input  gas and soot state, set by user.
/// @return soot oxidation rate (kg/m2*s)
///
////////////////////////////////////////////////////////////////////////////////

double oxidationModel_FAIR::getOxidationSootRate(const state &state) const {

    return 1.78E4 * sqrt(state.T) * exp(39E3 / (state.T*1.987)) * 
           state.getGasSpC(gasSp::O2);// * gasSpMW[(int)gasSp::C];    // kg_soot/m^2*s

}
