#include "sootModels/sootChemistry/oxidationModels/oxidationModel.h"
#include "sootDefs.h"

using namespace std;
using namespace soot;

////////////////////////////////////////////////////////////////////////////////

sourceTermStruct oxidationModel::getOxidationGasRates(const state& state, const double &X1) const {

    sourceTermStruct oxiGasSourceTerms;

    for (int sp=0; sp<(int)gasSp::size; sp++) {
        if(sp == (int)gasSp::C) continue;
        oxiGasSourceTerms.gasSourceTerms[sp] += X1 * oxidationRxnRatios[sp] * gasSpMW[sp] /
                                                (oxidationRxnRatios[(int)gasSp::C] * gasSpMW[(int)gasSp::C]) /
                                                state.rhoGas;
    }
    return oxiGasSourceTerms;
}
