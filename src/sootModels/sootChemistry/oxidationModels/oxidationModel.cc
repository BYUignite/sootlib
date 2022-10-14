#include "sootModels/sootChemistry/oxidationModels/oxidationModel.h"
#include "sootDefs.h"

using namespace std;
using namespace soot;

////////////////////////////////////////////////////////////////////////////////

oxidationModel::oxidationModel() {

    oxidationRxnRatios = vector<double>((int)gasSp::size, 0.0);
    oxidationRxnRatios[(int)gasSp::C] = 1.0;
}

////////////////////////////////////////////////////////////////////////////////

sourceTermStruct oxidationModel::getOxidationGasRates(const state& state, const double &X1) const {

    sourceTermStruct oxiGasSourceTerms;

    for (auto const& x : ggg) {

        gasSp sp = x.first;

        if (sp != gasSp::C)
            oxiGasSourceTerms.gasSourceTerms.at(sp) += X1 * oxidationRxnRatios[(int)sp] * gasSpMW[(int)sp]
                                                       / (oxidationRxnRatios[(int)gasSp::C] * gasSpMW[(int)gasSp::C])
                                                       / state.rhoGas;

    }

    return oxiGasSourceTerms;
}
