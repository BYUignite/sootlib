#include "nucleationModels/nucleationModel_MB.h"
#include "sootDefs.h"

using namespace std;
using namespace soot;

//////////////////////////////////////////////////////////////////////////////////////

nucleationModel_MB::nucleationModel_MB() : nucleationModel () {

    nucleationRxnRatios[(int)gasSp::C2H2] = -1;  // C2H2 --> 2C(soot) + H2 
    nucleationRxnRatios[(int)gasSp::H2]   =  1;
    nucleationRxnRatios[(int)gasSp::C]    =  2; 

    mechType = nucleationMech::MB;
}

//////////////////////////////////////////////////////////////////////////////////////
///
/// Nucleation by Brookes and Moss (1999)
///
/// Rate from Brookes and Moss (1999), Combustion and Flame, 116:486-503
/// Prediction of Soot and Thermal Radiation in Confined Turbulent Jet Diffusion Flames
///
/// C2H2 --> 2C(s) + H2 
/// @param state \input gas and soot state, set by user.
/// @return soot nucleation rate (\#/m3*s)
/// 
//////////////////////////////////////////////////////////////////////////////////////

double nucleationModel_MB::getNucleationSootRate(state &state) {

    // #/m3*s 
    return 54. * Na * state.getGasSpC(gasSp::C2H2) * exp(-21000. / state.T);
}

