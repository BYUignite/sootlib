#include "NucleationModel_LIN.h"
double soot::NucleationModel_LIN::getNucleationRate(const soot::GasState& gasState,
                                                    const soot::MomentSootState& sootState,
                                                    const std::vector<double>& particleSizes,
                                                    const std::vector<double>& particleWeights) const
{
	const double Rnuc = 0.63E4 * exp(-21100 / gasState.getT()) * gasState.getC_C2H2();
	return Rnuc * 2.0 * Na / sootState.getCMin();
}
