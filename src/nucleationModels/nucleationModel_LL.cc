#include "nucleationModels/nucleationModel_LL.h"
#include "sootDefs.h"

using namespace std;
using namespace soot;

////////////////////////////////////////////////////////////////////////////////

nucleationModel_LL::nucleationModel_LL() : nucleationModel () {

    nucleationRxnRatios[(int)gasSp::C2H2] = -1;   // C2H2 --> 2C(soot) + H2
    nucleationRxnRatios[(int)gasSp::H2]   =  1;
    nucleationRxnRatios[(int)gasSp::C]    =  2;

    mechType = nucleationMech::LL;
}

////////////////////////////////////////////////////////////////////////////////
///
/// Nucleation by Leung, Lindstedt, Jones (1991)
///
/// Rate from Leung, Lindstedt, Jones (1991), Comb. & Flame 87:289-305.
/// Returns chemical nucleation rate in #/m3*s.
///
/// C2H2 --> C(s) + H2
///
/// @param state \input  gas and soot state, set by user.
/// @return soot nucleation rate (\#/m3*s)
///
////////////////////////////////////////////////////////////////////////////////

double nucleationModel_LL::getNucleationSootRate(state &state) {

    //const double Rnuc = 0.1E5 * exp(-21100 / state.T) * state.getGasSpC(gasSp::C2H2);    // kmol/m3*s
    const double Rnuc = 0.1E5 * exp(-41100 / state.T) * state.getGasSpC(gasSp::C2H2);    // kmol/m3*s
    return Rnuc * 2 * Na / state.cMin;   // #/m3*s

}
