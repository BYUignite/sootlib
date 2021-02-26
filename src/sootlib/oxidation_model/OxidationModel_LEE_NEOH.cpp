#include "OxidationModel_LEE_NEOH.h"
double soot::OxidationModel_LEE_NEOH::getOxidationRate(const soot::State& gasState,
                                                       const soot::MomentSootState& sootState) const
{
	const double pO2_atm = gasState.getP_O2() / 101325.0;      // partial pressure of O2 (atm)
	const double pOH_atm = gasState.getP_OH() / 101325.0;      // partial pressure of OH (atm)

	const double rSootO2 = 1.085E4 * pO2_atm / sqrt(gasState.getT()) * exp(-1.977824E4 / gasState.getT()) / 1000.0;  // kg/m^2*s
	const double rSootOH = 1290.0 * 0.13 * pOH_atm / sqrt(gasState.getT());                        // kg/m^2*s

	return rSootO2 + rSootOH;
}
