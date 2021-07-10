#include "coagulationModel_FUCHS.h"

using namespace std;
using namespace soot;

double coagulationModel_FUCHS::getCoagulationSootRate(const state& state,
                                                      double m1,
                                                      double m2) const {

    JUtil::checkZero(rhoSoot, "rhoSoot");
    double Dp1 = pow(6 * abs(m1) / M_PI / rhoSoot, 1.0 / 3);
    double Dp2 = pow(6 * abs(m2) / M_PI / rhoSoot, 1.0 / 3);

    JUtil::checkZero(m1, "m1");
    JUtil::checkZero(m2, "m2");
    double c1 = sqrt(8 * kb * state.T / M_PI / m1);
    double c2 = sqrt(8 * kb * state.T / M_PI / m2);

    double Kn1 = 2 * state.getGasMeanFreePath() / Dp1;
    double Kn2 = 2 * state.getGasMeanFreePath() / Dp2;

    double Cc1 = 1 + Kn1 * (1.257 + 0.4 * exp(-1.1 / Kn1));       // Seinfeld p. 372 eq. 9.34. This is for air at 298 K, 1 atm
    double Cc2 = 1 + Kn2 * (1.257 + 0.4 * exp(-1.1 / Kn2));       // for D<<mfp_g, Cc = 1 + 1.657*Kn; Seinfeld p. 380: 10% error at Kn=1, 0% at Kn=0.01, 100

    JUtil::checkZero(state.muGas, "muGas");
    double D1 = kb * state.T * Cc1 / (3 * M_PI * state.muGas * Dp1);
    double D2 = kb * state.T * Cc2 / (3 * M_PI * state.muGas * Dp2);

    double l1 = 8 * D1 / M_PI / c1;
    double l2 = 8 * D2 / M_PI / c2;

    double g1 = sqrt(2) / 3 / Dp1 / l1 * (pow(Dp1 + l1, 3) - pow(Dp1 * Dp1 + l1 * l1, 3.0 / 2)) - sqrt(2) * Dp1;
    double g2 = sqrt(2) / 3 / Dp2 / l1 * (pow(Dp2 + l2, 3) - pow(Dp2 * Dp2 + l2 * l2, 3.0 / 2)) - sqrt(2) * Dp2;

    return 2 * M_PI * (D1 + D2) * (Dp1 + Dp2) / ((Dp1 + Dp2) / (Dp1 + Dp2 + 2 * sqrt(g1 * g1 + g2 * g2)) + 8 / eps_c * (D1 + D2) / sqrt(c1 * c1 + c2 * c2) / (Dp1 + Dp2));
}
