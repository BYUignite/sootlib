////////////////////////////////////////////////////////////////////////////////
/*! Oxidation by Lee et al. + Neoh
 *
 *      Rates from Lee et al. (1962) Comb. & Flame 6:137-145 and Neoh (1981)
 *      "Soot oxidation in flames" in Particulate Carbon Formation During
 *      Combustion book
 *      C + 0.5 O2 --> CO
 *      C + OH     --> CO + H
 *
 *      Returns chemical soot oxidation rate in kg/m2*s.
 *
 *      @param MomentState&     /input      local moment state; need M0 and M1
 *      @param rSoot            /output     soot growth rate (kg/m2*s)
 */

#include "OxidationModel_LEE_NEOH.h"

#include <cmath>

using namespace soot;

double OxidationModel_LEE_NEOH::getOxidationRate(const State& state, MassRateRatios& ratio) const {

    const double pO2_atm = state.getGasSpeciesP(GasSpecies::O2) / 101325.0;     // partial pressure of O2 (atm)
    const double pOH_atm = state.getGasSpeciesP(GasSpecies::OH) / 101325.0;     // partial pressure of OH (atm)

    const double rSootO2 = 1.085E4 * pO2_atm / sqrt(state.getT()) * exp(-1.977824E4 / state.getT()) / 1000.0;   // kg/m^2*s
    const double rSootOH = 1290 * 0.13 * pOH_atm / sqrt(state.getT());                                        // kg/m^2*s

    ratio.groOxi().gasSpeciesRatio(GasSpecies::O2) = -0.5 * MW_O2 / MW_C * rSootO2 / (rSootO2 + rSootOH);
    ratio.groOxi().gasSpeciesRatio(GasSpecies::OH) = -MW_OH / MW_C * rSootOH / (rSootO2 + rSootOH);
    ratio.groOxi().gasSpeciesRatio(GasSpecies::H) = MW_H / MW_C * rSootOH / (rSootO2 + rSootOH);
    ratio.groOxi().gasSpeciesRatio(GasSpecies::CO) = MW_CO / MW_C;

    return rSootO2 + rSootOH;
}
