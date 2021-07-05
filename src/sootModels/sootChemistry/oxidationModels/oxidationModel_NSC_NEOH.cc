////////////////////////////////////////////////////////////////////////////////
/*! Oxidation by NSC + Neoh
 *
 *      Rates from Nagle and Strickland-Constable (1961) and Neoh (1981) "Soot
 *      oxidation in flames" in Particulate Carbon Formation During Combustion
 *      book
 *      C + 0.5 O2 --> CO
 *      C + OH     --> CO + H
 *
 *      Returns chemical soot oxidation rate in kg/m2*s.
 *
 *      @param MomentState&     /input      local moment state; need M0 and M1
 *      @param rSoot            /output     soot growth rate (kg/m2*s)
 */

#include "oxidationModel_NSC_NEOH.h"

#include <cmath>

using namespace soot;

double OxidationModel_NSC_NEOH::getOxidationRate(const State& state, MassRateRatios& ratio) const {

    const double pO2_atm = state.getGasSpeciesP(GasSpecies::O2) / 101325.0; // partial pressure of O2 (atm)
    const double pOH_atm = state.getGasSpeciesP(GasSpecies::OH) / 101325.0; // partial pressure of OH (atm)

    const double kA = 20 * exp(-15098 / state.getT());              // rate constants
    const double kB = 4.46E-3 * exp(-7650 / state.getT());
    const double kT = 1.51E5 * exp(-48817 / state.getT());
    const double kz = 21.3 * exp(2063 / state.getT());

    const double x = 1 / (1 + kT / (kB * pO2_atm));                    // x = unitless fraction
    const double NSC_rate = kA * pO2_atm * x / (1 + kz * pO2_atm) + kB * pO2_atm * (1.0 - x);   // kmol/m^2*s
    const double rSootO2 = NSC_rate * state.getRhoSoot();                   // kg/m2*s
    const double rSootOH = 1290 * 0.13 * pOH_atm / sqrt(state.getT());    // kg/m2*s

    ratio.groOxi().gasSpeciesRatio(GasSpecies::O2) = -0.5 * MW_O2 / MW_C * rSootO2 / (rSootO2 + rSootOH);
    ratio.groOxi().gasSpeciesRatio(GasSpecies::OH) = -MW_OH / MW_C * rSootOH / (rSootO2 + rSootOH);
    ratio.groOxi().gasSpeciesRatio(GasSpecies::H) = MW_H / MW_C * rSootOH / (rSootO2 + rSootOH);
    ratio.groOxi().gasSpeciesRatio(GasSpecies::CO) = MW_CO / MW_C;

    return rSootO2 + rSootOH;                                               // kg/m2*s
}
