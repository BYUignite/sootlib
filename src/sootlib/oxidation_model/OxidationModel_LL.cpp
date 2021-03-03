#include "OxidationModel_LL.h"
double soot::OxidationModel_LL::getOxidationRate(const MomentState& state) const
{
	return 0.1E5 * sqrt(state.getT()) * exp(-19680.0 / state.getT()) * state.getGasSpeciesC(GasSpecies::C2H2) * MW_c;    // kg/m^2*s
}
