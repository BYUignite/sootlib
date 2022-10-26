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

double nucleationModel_LIN::getNucleationSootRate(state &state) {

    // #/m3*s
    return 0.63E4 * exp(-21100. / state.T) * state.getGasSpC(gasSp::C2H2) * 2.0 * Na / state.cMin;

}
