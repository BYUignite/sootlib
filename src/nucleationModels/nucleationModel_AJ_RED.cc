#include "nucleationModels/nucleationModel_AJ_RED.h"
#include "sootDefs.h"

using namespace std;
using namespace soot;

////////////////////////////////////////////////////////////////////////////////

nucleationModel_AJ_RED::nucleationModel_AJ_RED() : nucleationModel () {

    nucleationRxnRatios[(int)gasSp::C6H6] = -1;   // C6H6 --> 6C(soot) + 3H2
    nucleationRxnRatios[(int)gasSp::H2]   =  3;
    nucleationRxnRatios[(int)gasSp::C]    =  6;

    mechType = nucleationMech::AJ_RED;
}

////////////////////////////////////////////////////////////////////////////////
///
/// Nucleation by Alex Josephson (2018)
///
/// Rate from Josephson, Hopkins, Lignell, and Linn Combustion Theory and Modelling (2020)
/// Returns chemical nucleation rate in #/m3*s.
///
/// C2H2 --> C(s) + H2
///
/// @param state \input  gas, soot, and tar state, set by user.
/// @return soot nucleation rate (\#/m3*s)
///
////////////////////////////////////////////////////////////////////////////////

double nucleationModel_AJ_RED::getNucleationSootRate(state &state) {
    
    double eps = 2.2; // steric factor, the van der Waals enhancement factor
    double Bt; // frequency of collisions between tars
    double dtar; // effective tar diameter
    double da = 6.06E-9; // m // TODO: jansenpb --- what is da? using diameter of benzene for now

    dtar = da * sqrt(2*state.mtar/(3*12.011));

    Bt   = dtar*dtar * sqrt(8*M_PI*kb*state.T/state.mtar);


    const double Rnuc = eps*Bt*state.Ntar*state.Ntar;    // kmol/m3*s
    return Rnuc * 2 * Na / state.cMin;   // #/m3*s

}
