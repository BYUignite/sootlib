#include "GrowthModel_LL.h"
double soot::GrowthModel_LL::getGrowthRate(const soot::GasState& gasState, const soot::MomentSootState& sootState) const
{
	/**
	 * Growth by Leung_Lindstedt (1991)
	 *
	 * Rate from Leung & Lindstedt (1991), Comb. & Flame 87:289-305.
	 * Returns chemical surface growth rate in kg/m2*s.
	 *
	 * @param M0       /input  local soot number density (#/m3)
	 * @param M1       /input  local soot mass density (kg/m3)
	 */

	double Am2m3 = 0;
	const double cC2H2 = gasState.getC_C2H2();
	double rSoot = 0;

	const double M0 = sootState.getMoment(0);
	const double M1 = sootState.getMoment(1);

	if (M0 > 0.0)
		Am2m3 = M_PI * pow(std::abs(6 / (M_PI * sootState.getRho()) * M1 / M0), 2.0 / 3.0);

	if (Am2m3 > 0.0)
		rSoot = 0.6E4 * exp(-12100.0 / gasState.getT()) * cC2H2 / sqrt(Am2m3) * 2.0 * MW_C;

	return rSoot;
}
