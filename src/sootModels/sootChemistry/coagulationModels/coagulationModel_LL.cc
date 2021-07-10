#include "coagulationModel_LL.h"

using namespace std;
using namespace soot;

double coagulationModel_LL::getCoagulationSootRate(const state& state,
                                                   double m1,
                                                   double m2) const {

    double Ca = 9;
    double Dp1 = rhoSoot != 0 ? pow(6 * abs(m1) / M_PI / rhoSoot, 1.0 / 3) : 0;
    return rhoSoot != 0 ? 2 * Ca * sqrt(Dp1 * 6 * kb * state.T / rhoSoot) : 0;

}
