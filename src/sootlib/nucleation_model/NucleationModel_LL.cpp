#include "NucleationModel_LL.h"
double soot::NucleationModel_LL::getNucleationRate(MomentState& state,
                                                   const std::vector<double>& particleSizes,
                                                   const std::vector<double>& particleWeights) const
{
	const double Rnuc = 0.1E5 * exp(-21100 / state.getT()) * state.getGasSpeciesC(GasSpecies::C2H2);
	return Rnuc * 2.0 * Na / state.getCMin();
}
