#include "CoagulationModel_FUCHS.h"
double soot::CoagulationModel_FUCHS::getCoagulationRate(const soot::State& gasState,
                                                        const soot::MomentSootState& sootState,
                                                        double m1,
                                                        double m2) const
{
	const double Dp1 = pow(6.0 * abs(m1) / M_PI / sootState.getRho(), 1.0 / 3.0);
	const double Dp2 = pow(6.0 * abs(m2) / M_PI / sootState.getRho(), 1.0 / 3.0);

	const double c1 = sqrt(8.0 * kb * gasState.getT() / M_PI / m1);
	const double c2 = sqrt(8.0 * kb * gasState.getT() / M_PI / m2);

	const double Kn1 = 2.0 * gasState.getGasMeanFreePath() / Dp1;
	const double Kn2 = 2.0 * gasState.getGasMeanFreePath() / Dp2;

	const double Cc1 = 1 + Kn1 * (1.257 + 0.4 * exp(-1.1 / Kn1));
	const double Cc2 = 1 + Kn2 * (1.257 + 0.4 * exp(-1.1 / Kn2));

	const double D1 = kb * gasState.getT() * Cc1 / (3.0 * M_PI * gasState.getMu() * Dp1);
	const double D2 = kb * gasState.getT() * Cc2 / (3.0 * M_PI * gasState.getMu() * Dp2);

	const double l1 = 8.0 * D1 / M_PI / c1;
	const double l2 = 8.0 * D2 / M_PI / c2;

	const double g1 = sqrt(2.0) / 3.0 / Dp1 / l1 * (pow(Dp1 + l1, 3.0) - pow(Dp1 * Dp1 + l1 * l1, 3.0 / 2.0)) - sqrt(2.0) * Dp1;
	const double g2 = sqrt(2.0) / 3.0 / Dp2 / l1 * (pow(Dp2 + l2, 3.0) - pow(Dp2 * Dp2 + l2 * l2, 3.0 / 2.0)) - sqrt(2.0) * Dp2;

	return 2.0 * M_PI * (D1 + D2) * (Dp1 + Dp2) / ((Dp1 + Dp2) / (Dp1 + Dp2 + 2.0 * sqrt(g1 * g1 + g2 * g2)) + 8.0 / eps_c * (D1 + D2) / sqrt(c1 * c1 + c2 * c2) / (Dp1 + Dp2));
}
