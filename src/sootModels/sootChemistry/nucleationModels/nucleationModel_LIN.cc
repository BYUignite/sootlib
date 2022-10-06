#include "sootModels/sootChemistry/nucleationModels/nucleationModel_LIN.h"
#include "constants.h"

using namespace std;
using namespace soot;

////////////////////////////////////////////////////////////////////////////////

nucleationModel_LIN::nucleationModel_LIN() : nucleationModel () {

    nucleationRxnRatios.at(gasSp::C2H2) = -1;
    nucleationRxnRatios.at(gasSp::H2)   =  1;
    nucleationRxnRatios.at(gasSp::C)    =  2;

}

////////////////////////////////////////////////////////////////////////////////

double nucleationModel_LIN::getNucleationSootRate(state &state) {

    return 0.63E4 * exp(-21100 / state.T) * state.getGasSpC(gasSp::C2H2) * 2 * Na / state.cMin;

}
