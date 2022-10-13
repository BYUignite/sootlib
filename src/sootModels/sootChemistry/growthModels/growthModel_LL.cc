#include "sootModels/sootChemistry/growthModels/growthModel_LL.h"
#include "sootDefs.h"

using namespace std;
using namespace soot;

growthModel_LL::growthModel_LL() {

    growthRxnRatios.at(gasSp::C2H2) = -1;
    growthRxnRatios.at(gasSp::H2)   =  1;
    growthRxnRatios.at(gasSp::C)    =  2;

    mechType = growthMech::LL;
}

double growthModel_LL::getGrowthSootRate(const state &state) const {

    double Am2m3 = 0;           // soot surface area available for reaction (m2_soot/m3_total)
    double rSoot = 0;           // rate soot growth (kg/m2*s)

    double M0 = state.sootVar[0];
    double M1 = state.sootVar[1];

    if (M0 > 0)
        Am2m3 = M_PI * pow(abs(6 / (M_PI * rhoSoot) * M1 / M0), 2.0/3.0) * M0;

    if (Am2m3 > 0)
        rSoot = 0.6E4 * exp(-12100 / state.T) * state.getGasSpC(gasSp::C2H2) / sqrt(Am2m3) * 2 * gasSpMW[(int)gasSp::C];

    return rSoot;

}
