////////////////////////////////////////////////////////////////////////////////
/*! Coagulation by Leung_Lindstedt
 *
 *      Returns the value of the collision rate function beta in m3/#*s.
 *
 *      Note: this assumes the free molecular regime.
 *      The original LL model is for monodispersed and has the form
 *         2*Ca*sqrt(dp)*sqrt(6*kb*T/rhoSoot)
 *         This is Eq. (4) in LL but LL is missing the 1/2 power on (6*kb*T/rhoSoot)
 *
 *      @param MomentState&     \input      local moment state; need M0 and M1
 *      @param m1               \input      first particle size (kg)
 *      @param m2               \input      second particle size (kg)
 *
 */

#include "CoagulationModel_LL.h"

#include <cmath>

#include "lib/jutil/jutil.h"

using namespace std;
using namespace soot;

double CoagulationModel_LL::getCoagulationRate(const State& state,
                                               double m1,
                                               double m2) const {
    const double Ca = 9;
    JUtil::checkZero(state.getRhoSoot(), "rhoSoot");
    const double Dp1 = pow(6 * abs(m1) / M_PI / state.getRhoSoot(), 1.0 / 3);
    return 2 * Ca * sqrt(Dp1 * 6 * kb * state.getT() / state.getRhoSoot());
}
