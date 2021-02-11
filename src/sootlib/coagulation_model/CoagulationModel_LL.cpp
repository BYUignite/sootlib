#include "CoagulationModel_LL.h"
double soot::CoagulationModel_LL::getCoagulationRate(const soot::GasState& gasState,
                                                     const soot::MomentSootState& sootState,
                                                     double m1,
                                                     double m2) const
{
	const double Ca = 9.0;
	double Dp1 = pow(6.0 * abs(m1) / M_PI / sootState.getRho(), 1.0 / 3.0);
	return 2.0 * Ca * sqrt(Dp1 * 6.0 * kb * gasState.getT() / sootState.getRho());
}
