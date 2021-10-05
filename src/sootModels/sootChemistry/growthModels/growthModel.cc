#include "growthModel.h"

using namespace std;
using namespace soot;

////////////////////////////////////////////////////////////////////////////////

growthModel::growthModel() {

    growthRxnRatios = {{gasSp::C2H2, 0},
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

sourceTermStruct growthModel::getGrowthGasRates(const state &state, const double &G1) const {

    sourceTermStruct grwGasSourceTerms;

    //TODO verify that this works and loops over gas species properly
    for (auto const& x : growthRxnRatios) {

        gasSp sp = x.first;

        if (sp != gasSp::C)
            grwGasSourceTerms.gasSourceTerms.at(sp) += G1 * growthRxnRatios.at(sp) * gasSpMW.at(sp)
                                                       / (growthRxnRatios.at(gasSp::C) * gasSpMW.at(gasSp::C))
                                                       / state.rhoGas;

    }

    return grwGasSourceTerms;

}