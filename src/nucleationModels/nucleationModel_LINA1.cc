#include "nucleationModels/nucleationModel_LINA1.h"
#include "sootDefs.h"

using namespace std;
using namespace soot;

////////////////////////////////////////////////////////////////////////////////

nucleationModel_LINA1::nucleationModel_LINA1() : nucleationModel () {

    nucleationRxnRatios[(int)gasSp::C6H6] = -1;   // C6H6 --> 6C(soot) + 3H2
    nucleationRxnRatios[(int)gasSp::H2]   =  3;
    nucleationRxnRatios[(int)gasSp::C]    =  6;

    mechType = nucleationMech::LINA1;
}

////////////////////////////////////////////////////////////////////////////////
///
/// Growth by Lindstedt (1994)
///
/// C6H6 --> 6C(s) + 3H2
///
/// Rate from Bockhorn (1994) pg. 421, "Simplified Soot Nucleation and Surface Growth Steps..."
/// Equation (27.11), (27.13). Rate constants from Table 27.2. 
/// Rate constants listed there as reaction 27.11 and 27.12 look like they should be 27.10 and 27.11 (typo)
/// (See Proc. Comb. Inst. 30:775 for a comparison).
/// Returns nucleation rate in #/m3*s. 
///
/// @param state \input  gas and soot state, set by user.
/// @return soot nucleation rate (\#/m3*s)
///
////////////////////////////////////////////////////////////////////////////////

double nucleationModel_LINA1::getNucleationSootRate(state &state) {

    // #/m3*s
    return 0.75E5 * exp(-21100. / state.T) * state.getGasSpC(gasSp::C6H6) * 6.0 * Na / state.cMin;

}
