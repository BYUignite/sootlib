#include "sootModels/sootChemistry/nucleationModels/nucleationModel.h"
#include "sootDefs.h"

using namespace std;
using namespace soot;

////////////////////////////////////////////////////////////////////////////////

sourceTermStruct nucleationModel::getNucleationGasRates(const state& state, const double &N1) const {
    // Compute S in: d(rho*y_k)/dt + ... = ... + S
    // kg_k/m3*s (species k)

    sourceTermStruct nucGasSourceTerms;

    for (int sp=0; sp<(int)gasSp::size; sp++) {
        if(sp == (int)gasSp::C) continue;
            nucGasSourceTerms.gasSourceTerms[sp] += N1 * nucleationRxnRatios[sp] * gasSpMW[sp]
                                                       / (nucleationRxnRatios[(int)gasSp::C] * gasSpMW[(int)gasSp::C]);
    }
    return nucGasSourceTerms;
}

////////////////////////////////////////////////////////////////////////////////

sourceTermStruct nucleationModel::getNucleationPahRates(const state& state) const {

    sourceTermStruct nucPahSourceTerms;

    for (int sp=0; sp<(int)pahSp::size; sp++)
        nucPahSourceTerms.pahSourceTerms[sp] = nucleationPahRxnRates[sp];

    return nucPahSourceTerms;
}
