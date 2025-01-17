#include "nucleationModels/nucleationModel_BROWN.h"
#include "sootDefs.h"

using namespace std;
using namespace soot;

////////////////////////////////////////////////////////////////////////////

nucleationModel_BROWN::nucleationModel_BROWN() : nucleationModel () {

    nucleationRxnRatios[(int)gasSp::C2H2] = -1;
    nucleationRxnRatios[(int)gasSp::H2]   =  1;
    nucleationRxnRatios[(int)gasSp::C]    =  2;

    mechType = nucleationMech::BROWN;
}

/////////////////////////////////////////////////////////////////////////////
///
/// Soot formation by Brown and Fletcher 1998 (revised by Josephson and Lignell 2016)
///
/// @param state \input gas, soot and tar state, set by user
/// @return soot nucleation rate (\#/m3*s)
///
/////////////////////////////////////////////////////////////////////////////

double nucleationModel_BROWN::getNucleationSootRate(state &state) {
    
    double A_FC = 5.02E8;           //< 1/s 
    double E_FC = 1.989E8;          //< J/kmol

    const double Rnuc = state.tarVar[0] * A_FC * exp(-E_FC/(Rg*state.T)); // kg/m3*s 
    return Rnuc * 2 / gasSpMW[(int)gasSp::C] * Na / state.cMin; // #/m3*s
}
