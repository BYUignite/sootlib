#include "sootModels/sootChemistry/nucleationModels/nucleationModel.h"
#include "sootDefs.h"

using namespace std;
using namespace soot;

////////////////////////////////////////////////////////////////////////////////

nucleationModel::nucleationModel() : nucleationPahRxnRates{vector<double>{(int)pahSp::size, 0.0}} {

    nucleationRxnRatios = vector<double>((int)gasSp::size, 0.0);
    nucleationRxnRatios[(int)gasSp::C] = 1.0;
}

////////////////////////////////////////////////////////////////////////////////

sourceTermStruct nucleationModel::getNucleationGasRates(const state& state, const double &N1) const {

    sourceTermStruct nucGasSourceTerms;

    for (auto const& x : ggg) {

        gasSp sp = x.first;

        if (sp != gasSp::C) {
            nucGasSourceTerms.gasSourceTerms.at(sp) += N1 * nucleationRxnRatios[(int)sp] * gasSpMW[(int)sp]
                                                       / (nucleationRxnRatios[(int)gasSp::C] * gasSpMW[(int)gasSp::C])
                                                       / state.rhoGas;
        }
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
