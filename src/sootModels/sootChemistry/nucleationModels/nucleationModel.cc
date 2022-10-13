#include "sootModels/sootChemistry/nucleationModels/nucleationModel.h"
#include "sootDefs.h"

using namespace std;
using namespace soot;

////////////////////////////////////////////////////////////////////////////////

nucleationModel::nucleationModel() : nucleationPahRxnRates{vector<double>{(int)pahSp::size, 0.0}} {

    nucleationRxnRatios = {{gasSp::C2H2, 0},
                           {gasSp::O,    0},
                           {gasSp::O2,   0},
                           {gasSp::H,    0},
                           {gasSp::H2,   0},
                           {gasSp::OH,   0},
                           {gasSp::H2O,  0},
                           {gasSp::CO,   0},
                           {gasSp::C,    1},
                           {gasSp::C6H6, 0}};
}

////////////////////////////////////////////////////////////////////////////////

sourceTermStruct nucleationModel::getNucleationGasRates(const state& state, const double &N1) const {

    sourceTermStruct nucGasSourceTerms;

    for (auto const& x : nucleationRxnRatios) {

        gasSp sp = x.first;

        if (sp != gasSp::C) {
            nucGasSourceTerms.gasSourceTerms.at(sp) += N1 * nucleationRxnRatios.at(sp) * gasSpMW[(int)sp]
                                                       / (nucleationRxnRatios.at(gasSp::C) * gasSpMW[(int)gasSp::C])
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
