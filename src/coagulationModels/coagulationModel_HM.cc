#include "coagulationModels/coagulationModel_HM.h"
#include "sootDefs.h"

using namespace std;
using namespace soot;

////////////////////////////////////////////////////////////////////////////////
///
/// Coagulation as harmonic mean between FM and continuum regimes. 
///
/// FM and Continuum as outlined in Seinfeld and Pandis 3rd Ed. pages 372, 547, 548
/// See also Frenklach (2002) "Reaction mechanism of soot formation in flames"
/// Phys. Chem. Chem. Phys. 4 p 2028–2037.
///
/// @param state \input       gas and soot state, set by user.
/// @param m1               \input      first particle size (kg)
/// @param m2               \input      second particle size (kg)
/// @return coagulation rate (\#/m3*s)
///
////////////////////////////////////////////////////////////////////////////////

double coagulationModel_HM::getCoagulationSootRate(const state& state,
                                                      double m1,
                                                      double m2) const {

    if (m1 <= mmin || m2 <= mmin) return 0.0;

    double d1 = pow(6.*m1/(M_PI*rhoSoot), onethird);
    double d2 = pow(6.*m1/(M_PI*rhoSoot), onethird);
    double ds = d1 + d2;

    //------------ free molecular rate

    double mR = m1*m2/(m1+m2);                 // reduced mass
    double K12_FM = eps_c * sqrt(M_PI*kb*state.T*0.5/mR) * ds*ds * FM_multiplier; 

    //------------ continuum rate

    double mfp = state.getGasMeanFreePath();
    double Kn1 = 2*mfp/d1;
    double Kn2 = 2*mfp/d2;

    double Cc1 = 1 + Kn1 * (1.257 + 0.4*exp(-1.1/Kn1));   // Seinfeld p. 372 eq. 9.34. This is for air at 298 K, 1 atm
    double Cc2 = 1 + Kn2 * (1.257 + 0.4*exp(-1.1/Kn2));   // for D<<mfp_g, Cc = 1 + 1.657*Kn; Seinfeld p. 380: 10% error at Kn=1, 0% at Kn=0.01, 100

    double K12_C = twothird*kb*state.T/state.muGas *(Cc1/d1 + Cc2/d2)*ds;

    //------------ return harmonic mean

    return K12_FM*K12_C / (K12_FM + K12_C);
}
