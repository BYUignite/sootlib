#include "sootModels/sootChemistry/nucleationModels/nucleationModel_LIN.h"
#include "sootDefs.h"

using namespace std;
using namespace soot;

////////////////////////////////////////////////////////////////////////////////

nucleationModel_LIN::nucleationModel_LIN() : nucleationModel () {

    nucleationRxnRatios[gasSp::C2H2] = -1;
    nucleationRxnRatios[gasSp::H2]   =  1;
    nucleationRxnRatios[gasSp::C]    =  2;

    mechType = nucleationMech::LIN;
}

////////////////////////////////////////////////////////////////////////////////

double nucleationModel_LIN::getNucleationSootRate(state &state) {

    return 0.63E4 * exp(-21100. / state.T) * state.getGasSpC(gasSp::C2H2) * 2.0 * Na / state.cMin;

}
