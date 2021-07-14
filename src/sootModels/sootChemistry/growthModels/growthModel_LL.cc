#include "growthModel_LL.h"

using namespace std;
using namespace soot;

growthModel_LL::growthModel_LL() {

    growthRxnRatios->at(gasSp::C2H2) = -1;
    growthRxnRatios->at(gasSp::H2)   =  1;
    growthRxnRatios->at(gasSp::C)    =  2;

}

double growthModel_LL::getGrowthSootRate(const state &state) const {

    double Am2m3 = 0;           // soot surface area available for reaction (m2_soot/m3_total)
    double rSoot = 0;           // rate soot growth (kg/m2*s)

    if (state.sootVar[0] > 0)
        Am2m3 = M_PI * pow(abs(6 / (M_PI * rhoSoot) * state.sootVar[1] / state.sootVar[0]), 2.0 / 3) * abs(state.sootVar[0]);

    if (Am2m3 > 0)
        rSoot = 0.6E4 * exp(-12100 / state.T) * state.getGasSpC(gasSp::C2H2) / sqrt(Am2m3) * 2 * gasSpMW.at(gasSp::C);

    return rSoot;

}
