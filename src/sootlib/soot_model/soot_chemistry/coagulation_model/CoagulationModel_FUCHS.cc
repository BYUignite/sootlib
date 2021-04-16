////////////////////////////////////////////////////////////////////////////////
/*! Coagulation by Fuchs
 *
 *      Rate comes from Seinfeld and Pandis Atmospheric Chemistry book (2016), pg. 548, chp 13 
 *      (see also chapter 9). Details and clarification in Fuchs' Mechanics of Aerosols book (1964).
 *
 *      Seinfeld is missing the sqrt(2) in the final term for g. This is needed to reproduce 
 *      his plot. Fuchs' book has the sqrt(2). I've seen another book 
 *      (https://authors.library.caltech.edu/25069/7/AirPollution88-Ch5.pdf) with 1.0 in 
 *      place of both sqrt(2) factors. This gives 5% max error in the D=D curve.
 *
 *      Returns the value of the collision rate function beta in m3/#*s.
 *
 *      @param MomentState&     \input      local moment state; need M0 and M1
 *      @param m1               \input      first particle size (kg)
 *      @param m2               \input      second particle size (kg)
 */

#include "CoagulationModel_FUCHS.h"

#include <cmath>

using namespace std;
using namespace soot;

double CoagulationModel_FUCHS::getCoagulationRate(const State& state,
                                                  double m1,
                                                  double m2) const {

    const double Dp1 = pow(6 * abs(m1) / M_PI / state.getRhoSoot(), 1.0 / 3);
    const double Dp2 = pow(6 * abs(m2) / M_PI / state.getRhoSoot(), 1.0 / 3);

    const double c1 = sqrt(8 * kb * state.getT() / M_PI / m1);
    const double c2 = sqrt(8 * kb * state.getT() / M_PI / m2);

    const double Kn1 = 2 * state.getGasMeanFreePath() / Dp1;
    const double Kn2 = 2 * state.getGasMeanFreePath() / Dp2;

    const double Cc1 = 1 + Kn1 * (1.257 + 0.4 * exp(-1.1 / Kn1));       // Seinfeld p. 372 eq. 9.34. This is for air at 298 K, 1 atm
    const double Cc2 = 1 + Kn2 * (1.257 + 0.4 * exp(-1.1 / Kn2));       // for D<<mfp_g, Cc = 1 + 1.657*Kn; Seinfeld p. 380: 10% error at Kn=1, 0% at Kn=0.01, 100

    const double D1 = kb * state.getT() * Cc1 / (3 * M_PI * state.getMuGas() * Dp1);
    const double D2 = kb * state.getT() * Cc2 / (3 * M_PI * state.getMuGas() * Dp2);

    const double l1 = 8 * D1 / M_PI / c1;
    const double l2 = 8 * D2 / M_PI / c2;

    const double g1 = sqrt(2) / 3 / Dp1 / l1 * (pow(Dp1 + l1, 3) - pow(Dp1 * Dp1 + l1 * l1, 3.0 / 2)) - sqrt(2) * Dp1;
    const double g2 = sqrt(2) / 3 / Dp2 / l1 * (pow(Dp2 + l2, 3) - pow(Dp2 * Dp2 + l2 * l2, 3.0 / 2)) - sqrt(2) * Dp2;

    return 2 * M_PI * (D1 + D2) * (Dp1 + Dp2) / ((Dp1 + Dp2) / (Dp1 + Dp2 + 2 * sqrt(g1 * g1 + g2 * g2)) + 8 / eps_c * (D1 + D2) / sqrt(c1 * c1 + c2 * c2) / (Dp1 + Dp2));

}
