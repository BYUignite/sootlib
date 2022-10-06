#include "sootModels/sootChemistry/nucleationModels/nucleationModel_LL.h"

using namespace std;
using namespace soot;

////////////////////////////////////////////////////////////////////////////////

nucleationModel_LL::nucleationModel_LL() : nucleationModel () {

    nucleationRxnRatios.at(gasSp::C2H2) = -1;
    nucleationRxnRatios.at(gasSp::H2)   =  1;
    nucleationRxnRatios.at(gasSp::C)    =  2;

}

////////////////////////////////////////////////////////////////////////////////

double nucleationModel_LL::getNucleationSootRate(state &state) {

    const double Rnuc = 0.1E5 * exp(-21100 / state.T) * state.getGasSpC(gasSp::C2H2);    // kmol/m3*s
    return Rnuc * 2 * Na / state.cMin;   // #/m3*s

}
