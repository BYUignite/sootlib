#include "growthModel_LIN.h"

using namespace std;
using namespace soot;

growthModel_LIN::growthModel_LIN() {

    growthRxnRatios.at(gasSp::C2H2) = -1;
    growthRxnRatios.at(gasSp::H2)   =  1;
    growthRxnRatios.at(gasSp::C)    =  2;

}

double growthModel_LIN::getGrowthSootRate(const state &state) const {

    return 0.1E-11 * exp(-12100.0 / state.T) * state.getGasSpC(gasSp::C2H2) * state.sootMom[0] * 2 * gasSpMW.at(gasSp::C);     // kg/m2*s;

}
