#include "coagulationModels/coagulationModel_CONTINUUM.h"
#include "sootDefs.h"

using namespace std;
using namespace soot;

///////////////////////////////////////////////////////////////////////////////
///
/// Calculates coagulation rate in the continuum regime.
/// From Seinfeld and Pandis Atmospheric Chemistry book (2016), pg. 547, chp 13.
///
/// @param state \input       gas and soot state, set by user.
/// @param m1    \input
/// @param m2    \input
/// @return coagulation rate (\#/m3*s)
///
///////////////////////////////////////////////////////////////////////////////

double coagulationModel_CONTINUUM::getCoagulationSootRate(const state& state,
                                                          double m1,
                                                          double m2) const {

    if (m1 <= mmin || m2 <= mmin) return 0.0;

    double d1 = pow(6.*m1/(M_PI*rhoSoot), onethird);
    double d2 = pow(6.*m1/(M_PI*rhoSoot), onethird);
    double ds = d1 + d2;

    double mfp = state.getGasMeanFreePath();
    double Kn1 = 2*mfp/d1;
    double Kn2 = 2*mfp/d2;

    //----------- Cc1 = 1 + Kn1 * (1.257 + 0.4*exp(-1.1/Kn1)), was validated against 1+1.657*Kn1 and is very close for all Kn
    double Cc1 = 1 + 1.657*Kn1;   // Seinfeld p. 372 eq. 9.34. This is for air at 298 K, 1 atm
    double Cc2 = 1 + 1.657*Kn2;   // for D<<mfp_g, Cc = 1 + 1.657*Kn; Seinfeld p. 380: 10% error at Kn=1, 0% at Kn=0.01, 100

    double K12 = twothird*kb*state.T/state.muGas *(Cc1/d1 + Cc2/d2)*ds;

    return K12;
}
