#include "sootModels/sootChemistry/growthModels/growthModel.h"
#include "sootDefs.h"

using namespace std;
using namespace soot;

////////////////////////////////////////////////////////////////////////////////

sourceTermStruct growthModel::getGrowthGasRates(const state &state, const double &G1) const {

    sourceTermStruct grwGasSourceTerms;

    for (auto const& x : ggg) {

        gasSp sp = x.first;

        if (sp != gasSp::C)
            grwGasSourceTerms.gasSourceTerms.at(sp) += G1 * growthRxnRatios[(int)sp] * gasSpMW[(int)sp]
                                                       / (growthRxnRatios[(int)gasSp::C] * gasSpMW[(int)gasSp::C])
                                                       / state.rhoGas;

    }

    return grwGasSourceTerms;

}
