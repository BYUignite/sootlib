#include "OxidationModel_NSC_NEOH.h"
double soot::OxidationModel_NSC_NEOH::getOxidationRate(const soot::GasState& gasState,
                                                       const soot::SootState& sootState) const
{
	const double pO2_atm = gasState.getP_O2() / 101325.0; // partial pressure of O2 (atm)
	const double pOH_atm = gasState.getP_OH() / 101325.0; // partial pressure of OH (atm)

	const double kA = 20.0     * exp(-15098.0 / gasState.getT());                     // rate constants
	const double kB = 4.46E-3  * exp(-7650.0 / gasState.getT());
	const double kT = 1.51E5   * exp(-48817.0 / gasState.getT());
	const double kz = 21.3     * exp(2063.0 / gasState.getT());

	const double x  = 1.0 / (1.0 + kT / (kB * pO2_atm));                          // x = unitless fraction
	const double NSC_rate = kA * pO2_atm * x / (1.0 + kz * pO2_atm) + kB * pO2_atm * (1.0 - x);   // kmol/m^2*s
	const double rSootO2 = NSC_rate * sootState.getRho();                          // kg/m2*s
	const double rSootOH = 1290.0 * 0.13 * pOH_atm / sqrt(gasState.getT());                   // kg/m2*s

	return rSootO2 + rSootOH;                                   // kg/m2*s
}
