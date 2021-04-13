////////////////////////////////////////////////////////////////////////////////
/*! Growth by Leung_Lindstedt (1991)
 *
 *      Rate from Leung & Lindstedt (1991), Comb. & Flame 87:289-305.
 *      Returns chemical surface growth rate in kg/m2*s.
 *
 *      @param MomentState&     /input      local moment state; need M0 and M1
 *      @param rSoot            /output     soot growth rate (kg/m2*s)
 */

#include "GrowthModel_LL.h"

using namespace std;
using namespace soot;

double GrowthModel_LL::getGrowthRate(const State& state, MassRateRatios& ratio) const {

    double Am2m3 = 0;           // soot surface area available for reaction (m2_soot/m3_total)
    double rSoot = 0;           // rate soot growth (kg/m2*s)

    if (state.getMoment(0) > 0)
        Am2m3 = M_PI * pow(abs(6 / (M_PI * state.getRhoSoot()) * state.getMoment(1) / state.getMoment(0)), 2.0 / 3) * abs(state.getMoment(0));

    if (Am2m3 > 0)
        rSoot = 0.6E4 * exp(-12100 / state.getT()) * state.getGasSpeciesC(GasSpecies::C2H2) / sqrt(Am2m3) * 2 * MW_C;

    ratio.groOxi().gasSpeciesRatio(GasSpecies::C2H2) = -MW_C2H2 / (2 * MW_C);
    ratio.groOxi().gasSpeciesRatio(GasSpecies::H2) = MW_H2 / (2 * MW_C);

    return rSoot;

}
