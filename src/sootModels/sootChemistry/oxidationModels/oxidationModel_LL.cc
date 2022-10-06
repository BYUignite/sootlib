#include "sootModels/sootChemistry/oxidationModels/oxidationModel_LL.h"

using namespace std;
using namespace soot;

oxidationModel_LL::oxidationModel_LL() {

    oxidationRxnRatios.at(gasSp::CO) =  1;
    oxidationRxnRatios.at(gasSp::O2) = -0.5;
    oxidationRxnRatios.at(gasSp::C)  = -1;
}

double oxidationModel_LL::getOxidationSootRate(const state &state) const {

    return 0.1E5 * sqrt(state.T) * exp(-19680 / state.T) * state.getGasSpC(gasSp::C2H2) * gasSpMW.at(gasSp::C);    // kg/m^2*s

}
