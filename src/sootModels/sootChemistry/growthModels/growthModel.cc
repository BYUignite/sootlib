#include "sootModels/sootChemistry/growthModels/growthModel.h"
#include "sootDefs.h"

using namespace std;
using namespace soot;

////////////////////////////////////////////////////////////////////////////////

growthModel::growthModel() {

    growthRxnRatios = vector<double>((int)gasSp::size, 0.0);
    growthRxnRatios[(int)gasSp::C] = 1.0;

    // growthRxnRatios = {{gasSp::C2H2, 0},
    //                    {gasSp::O,    0},
    //                    {gasSp::O2,   0},
    //                    {gasSp::H,    0},
    //                    {gasSp::H2,   0},
    //                    {gasSp::OH,   0},
    //                    {gasSp::H2O,  0},
    //                    {gasSp::CO,   0},
    //                    {gasSp::C,    1},
    //                    {gasSp::C6H6, 0}};
}

////////////////////////////////////////////////////////////////////////////////

sourceTermStruct growthModel::getGrowthGasRates(const state &state, const double &G1) const {

    sourceTermStruct grwGasSourceTerms;

    // for (auto const& x : growthRxnRatios) {
    for (auto const& x : ggg) {

        gasSp sp = x.first;

        if (sp != gasSp::C)
            grwGasSourceTerms.gasSourceTerms.at(sp) += G1 * growthRxnRatios[(int)sp] * gasSpMW[(int)sp]
                                                       / (growthRxnRatios[(int)gasSp::C] * gasSpMW[(int)gasSp::C])
                                                       / state.rhoGas;

    }

    return grwGasSourceTerms;

}
