#include "nucleationModel.h"

using namespace std;
using namespace soot;

////////////////////////////////////////////////////////////////////////////////

nucleationModel::nucleationModel() {

    nucleationRxnRatios = {{gasSp::C2H2, 0},
                           {gasSp::O,    0},
                           {gasSp::O2,   0},
                           {gasSp::H,    0},
                           {gasSp::H2,   0},
                           {gasSp::OH,   0},
                           {gasSp::H2O,  0},
                           {gasSp::CO,   0},
                           {gasSp::C,    0},
                           {gasSp::C6H6, 0}};

    nucleationPahRxnRatios = {{pahSp::C10H8,  0},
                              {pahSp::C12H8,  0},
                              {pahSp::C12H10, 0},
                              {pahSp::C14H10, 0},
                              {pahSp::C16H10, 0},
                              {pahSp::C18H10, 0}};
}

////////////////////////////////////////////////////////////////////////////////

sourceTermStruct nucleationModel::getNucleationGasRates(const state& state, const double &N1) const {

    sourceTermStruct nucGasSourceTerms;

    //TODO verify that this works properly
    for (auto const& x : nucleationRxnRatios) {

        gasSp sp = x.first;

        if (sp != gasSp::C)
            nucGasSourceTerms.gasSourceTerms.at(sp) += N1 * nucleationRxnRatios.at(sp) * gasSpMW.at(sp)
                                                       / (nucleationRxnRatios.at(gasSp::C) * gasSpMW.at(gasSp::C))
                                                       / state.rhoGas;
    }

    return nucGasSourceTerms;
}


