#include "state.h"

#include <numeric>

using namespace soot;
using namespace std;

////////////////////////////////////////////////////////////////////////////////
/// 
/// Sets the thermodynamic state based on user input
/// 
/// Only point of contact between users and the state class. User provides
/// relevant data to be assigned to sootlib's internal state variables.
/// 
/// @param T_           temperature (K)
/// @param P_           pressure (Pa)
/// @param rhoGas_      density of gas mixture (kg/m3)
/// @param MWGas_       gas mixture molecular weight (kg/kmol)
/// @param yGas_        gas species mass fractions [H, H2, O, O2, OH, H2O, CO, C2H2]
/// @param yPAH_        PAH species mass fractions [C10H8, C12H8, C12H10, C14H10, C16H10, C18H10]
/// @param sootVar_     soot variable (moments or section values) values
/// @param cMin_        minimum number of carbon atoms in a soot particle
/// 
/// IMPORTANT: gas and PAH species mass fractions MUST be provided in the order specified
/// above within the yGas and yPAH vectors. Values must be non-negative. If a species is
/// not represented or not present, DO NOT leave it out; instead, enter a mass fraction
/// value of zero. If the user mechanism contains more than one species with the same
/// molecular formula (C16H10 is a common culprit), enter the sum of the mass fractions
/// for the applicable species. Any additional species information is not used by sootlib
/// and will be ignored.
/// 
////////////////////////////////////////////////////////////////////////////////

void state::setState(double T_, double P_, double rhoGas_, double muGas_, double MWGas_,
                     vector<double> yGas_, vector<double> yPah_, vector<double> sootVar_, int nsoot_, double cMin_) {

    //------------ scalar variable values

    if (T_ <= 0) throw domain_error("Unphysical state value input: T");
    else T = T_;

    if (P_ <= 0) throw domain_error("Unphysical state value input: P");
    else P = P_;

    if (rhoGas_ <= 0) throw domain_error("Unphysical state value input: rhoGas");
    else rhoGas = rhoGas_;

    if (muGas_ <= 0) throw domain_error("Unphysical state value input: muGas");
    else muGas = muGas_;

    if (MWGas_ <= 0) throw domain_error("Unphysical state value input: MWGas");
    else MWGas = MWGas_;

    if (cMin_ <= 0) throw domain_error("Unphysical state value input: cMin");
    else cMin = cMin_;

    //------------ soot moments/bins

    nsoot = nsoot_;
    for (double s : sootVar_)
        if (s < 0)
            throw domain_error("Unphysical state value input: negative soot moment(s)");

    sootVar = sootVar_;

    //------------ gas species mass fractions

    for (double y : yGas_) {
        if (y < 0) {
            y = 0;
        }
        if (y > 1)
            throw domain_error("Unphysical state value input: gas species mass fraction > 1.0");
    }

    double yGas_sum = 0;
    for(double y : yGas_)
        yGas_sum += y;
    if (yGas_sum > 1.0)
        throw domain_error("Unphysical state value input: sum of gas species mass fractions greater than one");

    yGas = yGas_;

    //------------ PAH mass fractions

    if (yPah_.size() != (yPah.size()))
        throw domain_error("Invalid input vector size: PAH species mass fractions");

    for (double y : yPah_)
        if (y < 0 || y > 1)
            throw domain_error("Unphysical state value input: PAH species mass fraction(s)");

    double yPAH_sum = 0;
    for(double y :yPah_)
        yPAH_sum += y;
    if (yPAH_sum > 1.0)
        throw domain_error("Unphysical state value input: sum of PAH species mass fractions greater than one");

    yPah = yPah_;

}

////////////////////////////////////////////////////////////////////////////////

