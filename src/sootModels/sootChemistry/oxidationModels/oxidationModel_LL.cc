#include "sootModels/sootChemistry/oxidationModels/oxidationModel_LL.h"
#include "sootDefs.h"

using namespace std;
using namespace soot;

oxidationModel_LL::oxidationModel_LL() {

    oxidationRxnRatios[gasSp::CO] =  1;
    oxidationRxnRatios[gasSp::O2] = -0.5;
    oxidationRxnRatios[gasSp::C]  = -1;

    mechType = oxidationMech::LL;
}

double oxidationModel_LL::getOxidationSootRate(const state &state) const {

    return 0.1E5 * sqrt(state.T) * exp(-19680. / state.T) * 
           state.getGasSpC(gasSp::O2) * gasSpMW[(int)gasSp::C];    // kg_soot/m^2*s

}
