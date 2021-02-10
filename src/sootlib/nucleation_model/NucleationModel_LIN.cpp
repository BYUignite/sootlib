#include "NucleationModel_LIN.h"
double soot::NucleationModel_LIN::getNucleationRate(const soot::GasState& gasState,
                                                    const soot::MomentSootState& sootState) const
{
	double cC2H2 = gasState.getC_C2H2();   // kmol/m3
	double Rnuc  =  0.63E4 * exp(-21100.0 / gasState.getT()) * cC2H2;       // kmol/m^3*s

	return Rnuc * 2 * Na / sootState.getCmin();                          // #/m3*s
}
