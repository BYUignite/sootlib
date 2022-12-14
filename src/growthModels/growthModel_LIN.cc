#include "growthModels/growthModel_LIN.h"
#include "sootDefs.h"

using namespace std;
using namespace soot;

////////////////////////////////////////////////////////////////////////////////

growthModel_LIN::growthModel_LIN() {

    growthRxnRatios[(int)gasSp::C2H2] = -1;    // C2H2 --> 2C(soot) + H2
    growthRxnRatios[(int)gasSp::H2]   =  1;
    growthRxnRatios[(int)gasSp::C]    =  2;

    mechType = growthMech::LIN;
}

////////////////////////////////////////////////////////////////////////////////
///
/// Growth by Lindstedt (1994)
///
/// Rate from Bockhorn (1994) pg. 417, "Simplified Soot Nucleation and Surface Growth Steps..."
/// Equation (27.36). Returns chemical surface growth rate in kg/m2*s. Assumes that rate is
/// proportional to number of particles (M0) but independent of available surface area.
///
/// @param state       \input  gas and soot state, set by user.
/// @return soot growth rate (kg/m2*s)
///
////////////////////////////////////////////////////////////////////////////////

double growthModel_LIN::getGrowthSootRate(const state &state) const {

    return 750.*exp(-12100./state.T)*state.getGasSpC(gasSp::C2H2) * 
           2. * gasSpMW[(int)gasSp::C];        // kg_soot/m2*s

}
