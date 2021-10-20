#include "oxidationModel.h"

using namespace std;
using namespace soot;

////////////////////////////////////////////////////////////////////////////////

oxidationModel::oxidationModel() {

    oxidationRxnRatios = {{gasSp::C2H2, 0},
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

sourceTermStruct oxidationModel::getOxidationGasRates(const state& state, const double &X1) const {

    sourceTermStruct oxiGasSourceTerms;

    for (auto const& x : oxidationRxnRatios) {

        gasSp sp = x.first;

        if (sp != gasSp::C)
            oxiGasSourceTerms.gasSourceTerms.at(sp) += X1 * oxidationRxnRatios.at(sp) * gasSpMW.at(sp)
                                                       / (oxidationRxnRatios.at(gasSp::C) * gasSpMW.at(gasSp::C))
                                                       / state.rhoGas;

    }

    return oxiGasSourceTerms;
}