#include "OxidationModel_LEE_NEOH.h"
double soot::OxidationModel_LEE_NEOH::getOxidationRate(const MomentState& state) const
{
	const double pO2_atm = state.getGasSpeciesP(GasSpecies::O2) / 101325.0;      // partial pressure of O2 (atm)
	const double pOH_atm = state.getGasSpeciesP(GasSpecies::OH) / 101325.0;      // partial pressure of OH (atm)

	const double rSootO2 = 1.085E4 * pO2_atm / sqrt(state.getT()) * exp(-1.977824E4 / state.getT()) / 1000.0;  // kg/m^2*s
	const double rSootOH = 1290.0 * 0.13 * pOH_atm / sqrt(state.getT());                        // kg/m^2*s

	return rSootO2 + rSootOH;
}
