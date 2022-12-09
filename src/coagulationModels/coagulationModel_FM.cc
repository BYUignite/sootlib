#include "coagulationModels/coagulationModel_FM.h"
#include "sootDefs.h"

using namespace std;
using namespace soot;

///////////////////////////////////////////////////////////////////////////////
///
/// Calculates coagulation rate in the free molecular regime.
/// From Seinfeld and Pandis Atmospheric Chemistry book (2016), pg. 548, chp 13.
///
/// @param state \input       gas and soot state, set by user.
/// @param m1    \input
/// @param m2    \input
/// @return coagulation rate (\#/m3*s)
///
///////////////////////////////////////////////////////////////////////////////

double coagulationModel_FM::getCoagulationSootRate(const state& state,
                                                   double m1,
                                                   double m2) const {

    if (m1 <= mmin || m2 <= mmin) return 0.0;

    double m13_m13 = pow(m1, onethird) + pow(m2, onethird);

    double K12 = eps_c * sqrt(0.5*M_PI*kb*state.T)*pow(6./(M_PI/rhoSoot), twothird) *
                         sqrt(1/m1 + 1/m2)*m13_m13*m13_m13;
                  
    return K12 * FM_multiplier;      // make FM_multiplier = 9/2/eps_c for LL
}
