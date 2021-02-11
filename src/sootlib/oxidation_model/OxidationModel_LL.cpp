#include "OxidationModel_LL.h"
double soot::OxidationModel_LL::getOxidationRate(const soot::GasState& gasState, const soot::MomentSootState& sootState) const
{
	return 0.1E5 * sqrt(gasState.getT()) * exp(-19680.0 / gasState.getT()) * gasState.getC_O2() * MW_c;    // kg/m^2*s
}
