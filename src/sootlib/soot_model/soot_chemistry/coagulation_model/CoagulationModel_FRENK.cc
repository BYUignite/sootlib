////////////////////////////////////////////////////////////////////////////////
/*! Coagulation by Frenklach
 *
 *      Returns the value of the collision rate function beta in m3/#*s.
 *
 *      @param MomentState&     \input      local moment state; need M0 and M1
 *      @param m1               \input      first particle size (kg)
 *      @param m2               \input      second particle size (kg)
 *
 */

#include "CoagulationModel_FRENK.h"

#include <cmath>

#include "lib/jutil/jutil.h"

using namespace std;
using namespace soot;

double CoagulationModel_FRENK::getCoagulationRate(const State& state,
                                                  double m1,
                                                  double m2) const {

    JUtil::checkZero(state.getRhoSoot(), "rhoSoot");
    const double Dp1 = pow(6 * abs(m1) / M_PI / state.getRhoSoot(), 1.0 / 3);
    const double Dp2 = pow(6 * abs(m2) / M_PI / state.getRhoSoot(), 1.0 / 3);

    //------------ free molecular rate
    JUtil::checkZero(m1 + m2, "m1 + m2");
    const double m12 = abs(m1 * m2 / (m1 + m2));
    const double beta_12_FM = eps_c * sqrt(M_PI * kb * state.getT() * 0.5 / m12) * pow(Dp1 + Dp2, 2);

    //------------ continuum rate
    const double Kn1 = 2 * state.getGasMeanFreePath() / Dp1;
    const double Kn2 = 2 * state.getGasMeanFreePath() / Dp2;

    const double Cc1 = 1 + Kn1 * (1.257 + 0.4 * exp(-1.1 / Kn1));   // Seinfeld p. 372 eq. 9.34. This is for air at 298 K, 1 atm
    const double Cc2 = 1 + Kn2 * (1.257 + 0.4 * exp(-1.1 / Kn2));   // for D<<mfp_g, Cc = 1 + 1.657*Kn; Seinfeld p. 380: 10% error at Kn=1, 0% at Kn=0.01, 100

    JUtil::checkZero(state.getMuGas());
    const double beta_12_C = 2 * kb * state.getT() / (3 * state.getMuGas()) * (Cc1 / Dp1 + Cc2 / Dp1) * (Dp1 + Dp2);

    //------------ return harmonic mean
    return beta_12_FM * beta_12_C / (beta_12_FM + beta_12_C);

}
