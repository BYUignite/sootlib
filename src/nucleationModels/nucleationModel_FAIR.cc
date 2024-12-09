#include "nucleationModels/nucleationModel_FAIR.h"
#include "sootDefs.h"

using namespace std;
using namespace soot;

////////////////////////////////////////////////////////////////////////////////

nucleationModel_FAIR::nucleationModel_FAIR() : nucleationModel () {

    nucleationRxnRatios[(int)gasSp::C2H2] = -1;   // C2H2 --> 2C(soot) + H2
    nucleationRxnRatios[(int)gasSp::H2]   =  1;
    nucleationRxnRatios[(int)gasSp::C]    =  2;

    mechType = nucleationMech::FAIR;
}

////////////////////////////////////////////////////////////////////////////////
///
/// Nucleation by Fairweather (1992)
///
/// Rate from Predictions of Radiative Transfer from a Turbulent Reacting Jet in a Cross-Wind (1992)
/// Combustion and Flame 89: 45-63 Fairweather, Jones, and Lindstedt
/// Returns chemical nucleation rate in #/m3*s.
///
/// C2H2 --> 2C(s) + H2
///
/// @param state \input  gas and soot state, set by user.
/// @return soot nucleation rate (\#/m3*s)
///
////////////////////////////////////////////////////////////////////////////////

double nucleationModel_FAIR::getNucleationSootRate(state &state) {

    // #/m3*s
    return 1.35E6 * exp(-41E3 / (state.T*1.987)) * state.getGasSpC(gasSp::C2H2) * 2.0 * Na / state.cMin;

}
