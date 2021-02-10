#include "OxidationModel_LL.h"
double soot::OxidationModel_LL::getOxidationRate(const soot::GasState& gasState, const soot::MomentSootState& sootState) const
{
	double cO2 = gasState.getC_O2();             // kmol/m3
	double rSoot = 0.1E5 * sqrt(gasState.getT()) * exp(-19680.0 / gasState.getT()) * cO2 * MW_c;    // kg/m^2*s

	return rSoot;
}
