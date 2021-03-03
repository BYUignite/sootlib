#include "CoagulationModel_LL.h"
double soot::CoagulationModel_LL::getCoagulationRate(const MomentState& state,
                                                     double m1,
                                                     double m2) const
{
	const double Ca = 9.0;
	double Dp1 = pow(6.0 * std::abs(m1) / M_PI / state.getRhoSoot(), 1.0 / 3.0);
	return 2.0 * Ca * sqrt(Dp1 * 6.0 * kb * state.getT() / state.getRhoSoot());
}
