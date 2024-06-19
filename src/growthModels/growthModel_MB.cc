#include "growthModels/growthModel_MB.h"
#include "sootDefs.h"
#include "sootModel.h"                // for the SM back pointer

using namespace std;
using namespace soot;

/////////////////////////////////////////////////////////////////////////

growthModel_MB::growthModel_MB() {

    growthRxnRatios[(int)gasSp::C2H2] = -1;        // C2H2 --> 2C(soot) + H2 
    growthRxnRatios[(int)gasSp::H2]   =  1;
    growthRxnRatios[(int)gasSp::C]    =  2;

    mechType = growthMech::MB;
}

/////////////////////////////////////////////////////////////////////////
///
/// Growth by Moss-Brookes (1999)
///
/// Rate from Moss-Brookes (1999) Predictions of Soot and Thermal Radiation Properties...
/// Returns chemical surface growth rate in kg/m2*s.
///
/// Using model params n = 1, a = 54, m = 1/4, and b = 6.90
/// C2H2 + nC(s) --> (n+2)C(s) + H2 
///
/// @param state       \input gas and soot state, set by user.
/// @return soot growth rate (kg/m2*s)
///
/////////////////////////////////////////////////////////////////////////

double growthModel_MB::getGrowthSootRate(const state &state) const {

    double Am2m3 = 0;            // soot surface area available for reaction (m2_soot/m3_total)
    double rSoot = 0;            // rate soot growth (kg/m2*s)

    double M0, M1;               // #/m3, kg/m3 

    if (SM->psdMechType == psdMech::SECT) {
        M0 = SM->get_M0_sectional(state);
        M1 = SM->get_M1_sectional(state);
    }
    else {
        M0 = state.sootVar[0];
        M1 = state.sootVar[1];
    }

    if (M0 > 0)
        Am2m3 = pow( pow(M_PI * M0, 1.0/3.0) * pow(6 * M1 / rhoSoot, 2.0/3.0), 1.0); // power 1.0 = n

    if (Am2m3 > 0)
        rSoot = 6.90 * pow(state.getGasSpC(gasSp::C2H2), 1.0/4.0) * exp(-12100 / state.T) * Am2m3;

    return rSoot;
}

