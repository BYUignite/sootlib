#include "tarModels/tarModel_BROWN.h"
#include "sootDefs.h"

using namespace std;
using namespace soot;

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
///
/// Tar oxidation (cracking) and tar gasification (surface reaction) (2016; originally 1998)
/// 
/// Rates from Alex Josephson "Revision to Modeling Soot Derived from Pulverized Coal"
/// 
///
/// @param state \input gas, soot, and tar state, set by user.
/// @return tar reaction rates 
///
//////////////////////////////////////////////////////////////////////////

double tarModel_BROWN::getCrackingTarRate(state &state) {

    // tar oxidation

    double A_OT   = 6.77E5; //> m3/kg*s
    double E_OT   = 5.23E7; //> J/kmol
    double rho_O2 = state.getGasSpC(gasSp::O2) * gasSpMW[(int)gasSp::O2];

    return state.tarVar[0] * rho_O2 * A_OT * exp(-E_OT/(Rg*state.T));

}

double tarModel_BROWN::getSurfaceTarRate(state &state) {

    // tar gasification

    double A_GT = 9.77E10; //> 1/s 
    double E_GT = 2.869E8; //> J/kmol 

    return state.tarVar[0] * A_GT * exp(-E_GT/(Rg*state.T));
}
