////////////////////////////////////////////////////////////////////////////////
/*! Oxidation by Leung_Lindstedt (1991)
 *
 *      Rate from Leung & Lindstedt (1991), Comb. & Flame 87:289-305.
 *      Returns chemical soot oxidation rate in kg/m2*s.
 *
 *      C + 0.5 O2 --> CO
 *
 *      @param MomentState&     /input      local moment state; need M0 and M1
 *      @param rSoot            /output     soot growth rate (kg/m2*s)
 */

#include "OxidationModel_LL.h"

using namespace soot;

double OxidationModel_LL::getOxidationRate(const InputState& state, MassRateRatios& ratio) const {

    ratio.groOxi().gasSpeciesRatio(GasSpecies::O2) = -0.5 * MW_O2 / MW_C;
    ratio.groOxi().gasSpeciesRatio(GasSpecies::CO) = MW_CO / MW_C;

    return 0.1E5 * sqrt(state.getT()) * exp(-19680.0 / state.getT()) * state.getGasSpeciesC(GasSpecies::C2H2)
        * MW_C;    // kg/m^2*s
}
