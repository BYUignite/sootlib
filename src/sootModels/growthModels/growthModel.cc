#include "sootModels/sootChemistry/growthModels/growthModel.h"
#include "sootDefs.h"

using namespace std;
using namespace soot;

////////////////////////////////////////////////////////////////////////////////

sourceTermStruct growthModel::getGrowthGasRates(const state &state, const double &G1) const {
    // Compute S in: d(rho*y_k)/dt + ... = ... + S
    // kg_k/m3*s (species k)

    sourceTermStruct grwGasSourceTerms;

    for (int sp=0; sp<(int)gasSp::size; sp++) {
        if(sp == (int)gasSp::C) continue;
            grwGasSourceTerms.gasSourceTerms[sp] += G1 * growthRxnRatios[sp] * gasSpMW[sp] /
                                                    (growthRxnRatios[(int)gasSp::C] * gasSpMW[(int)gasSp::C]);
    }
    return grwGasSourceTerms;
}
