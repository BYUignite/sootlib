#include "CoagulationModel_FRENK.h"
double soot::CoagulationModel_FRENK::getCoagulationRate(const soot::GasState& gasState,
                                                        const soot::MomentSootState& sootState,
                                                        double m1,
                                                        double m2) const
{
	const double Dp1 = pow(6.0 * std::abs(m1) / M_PI / sootState.getRho(), 1.0 / 3.0);
	const double Dp2 = pow(6.0 * std::abs(m2) / M_PI / sootState.getRho(), 1.0 / 3.0);

	const double m12 = std::abs(m1 * m2 / (m1 + m2));

	const double beta_12_FM = eps_c * sqrt(M_PI * kb * gasState.getT() * 0.5 / m12) * pow(Dp1 + Dp2, 2.0);

	const double Kn1 = 2.0 * gasState.getGasMeanFreePath() / Dp1;
	const double Kn2 = 2.0 * gasState.getGasMeanFreePath() / Dp2;

	const double Cc1 = 1 + Kn1 * (1.257 + 0.4 * exp(-1.1 / Kn1));
	const double Cc2 = 1 + Kn2 * (1.257 + 0.4 * exp(-1.1 / Kn2));

	double beta_12_C = 2.0 * kb * gasState.getT() / (3.0 * gasState.getMu()) * (Cc1 / Dp1 + Cc2 / Dp1) * (Dp1 + Dp2);

	return beta_12_FM * beta_12_C / (beta_12_FM + beta_12_C);
}
