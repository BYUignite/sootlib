#include "growthModels/growthModel_LL.h"
#include "sootDefs.h"
#include "sootModel.h"          // for the SM back pointer

using namespace std;
using namespace soot;

//////////////////////////////////////////////////////////////////////////////////

growthModel_LL::growthModel_LL() {

    growthRxnRatios[(int)gasSp::C2H2] = -1;    // C2H2 --> 2C(soot) + H2
    growthRxnRatios[(int)gasSp::H2]   =  1;
    growthRxnRatios[(int)gasSp::C]    =  2;

    mechType = growthMech::LL;
}

//////////////////////////////////////////////////////////////////////////////////
///
/// Growth by Leung_Lindstedt (1991)
///
/// Rate from Leung & Lindstedt (1991), Comb. & Flame 87:289-305.
/// Returns chemical surface growth rate in kg/m2*s.
///
/// C2H2 + nC(s) --> (n+2)C(s) + H2
///
/// @param state       \input  gas and soot state, set by user.
/// @return soot growth rate (kg/m2*s)
///
//////////////////////////////////////////////////////////////////////////////////

double growthModel_LL::getGrowthSootRate(const state &state) const {

    double Am2m3 = 0;           // soot surface area available for reaction (m2_soot/m3_total)
    double rSoot = 0;           // rate soot growth (kg/m2*s)

    double M0, M1;                       // #/m3, kg/m3

    if (SM->psdMechType == psdMech::SECT) {
        M0 = SM->get_M0_sectional(state);
        M1 = SM->get_M1_sectional(state);
    }
    else {
        M0 = state.sootVar[0];
        M1 = state.sootVar[1];
    }

    if (M0 > 0)
        Am2m3 = M_PI * pow(6 / (M_PI * rhoSoot) * M1 / M0, 2.0/3.0) * M0;

    if (Am2m3 > 0)
        rSoot = 0.6E4 * exp(-12100 / state.T) * state.getGasSpC(gasSp::C2H2) / sqrt(Am2m3) * 2 * gasSpMW[(int)gasSp::C];

    return rSoot;

}
