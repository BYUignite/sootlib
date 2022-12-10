#include "nucleationModels/nucleationModel_LIN.h"
#include "sootDefs.h"

using namespace std;
using namespace soot;

////////////////////////////////////////////////////////////////////////////////

nucleationModel_LIN::nucleationModel_LIN() : nucleationModel () {

    nucleationRxnRatios[(int)gasSp::C2H2] = -1;   // C2H2 --> 2C(soot) + H2
    nucleationRxnRatios[(int)gasSp::H2]   =  1;
    nucleationRxnRatios[(int)gasSp::C]    =  2;

    mechType = nucleationMech::LIN;
}

////////////////////////////////////////////////////////////////////////////////
///
/// Nucleation by Lindstedt (2005)
///
/// Rate from Lindstedt (2005), Proc. Comb. Inst. 30:775
/// Returns chemical nucleation rate in #/m3*s.
///
/// C2H2 --> 2C(s) + H2
///
/// @param state \input  gas and soot state, set by user.
/// @return soot nucleation rate (\#/m3*s)
///
////////////////////////////////////////////////////////////////////////////////

double nucleationModel_LIN::getNucleationSootRate(state &state) {

    // #/m3*s
    return 0.63E4 * exp(-21100. / state.T) * state.getGasSpC(gasSp::C2H2) * 2.0 * Na / state.cMin;

}
