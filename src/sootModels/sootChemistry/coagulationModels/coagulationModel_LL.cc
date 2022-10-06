#include "sootModels/sootChemistry/coagulationModels/coagulationModel_LL.h"

using namespace std;
using namespace soot;

double coagulationModel_LL::getCoagulationSootRate(const state& state,
                                                   double m1,
                                                   double m2) const {

    if (m1 == 0 || m2 == 0)
        return 0;

    double Ca = 9;
    double Dp1 = pow(6 * abs(m1) / M_PI / rhoSoot, 1.0 / 3);
    return 2 * Ca * sqrt(Dp1 * 6 * kb * state.T / rhoSoot);

}
