////////////////////////////////////////////////////////////////////////////////
/*! Growth by Lindstedt (1994)
 *
 *      Rate from Bockhorn (1994) pg. 417, "Simplified Soot Nucleation and Surface Growth Steps..."
 *      Equation (27.35). Returns chemical surface growth rate in kg/m2*s.
 *
 *      @param MomentState&     /input      local moment state; need M0 and M1
 *      @param rSoot            /output     soot growth rate (kg/m2*s)
 */

#include "GrowthModel_LIN.h"

double soot::GrowthModel_LIN::getGrowthRate(const MomentState& state) const {
	
	const double rSoot = 750.0 * exp(-12100.0 / state.getT()) * state.getGasSpeciesC(GasSpecies::C2H2) * 2.0 * MW_C;     // kg/m2*s

	return rSoot;       // kg/m2*s

}
