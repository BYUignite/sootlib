////////////////////////////////////////////////////////////////////////////////
/*! Nucleation by Leung_Lindstedt (1991)
 *
 *      Rate from Leung & Lindstedt (1991), Comb. & Flame 87:289-305.
 *      Returns chemical nucleation rate in #/m3*s.
 *
 */

#include "nucleationModel_LL.h"

#include <cmath>

using namespace std;
using namespace soot;

double NucleationModel_LL::getNucleationRate(State& state,
                                             const vector<double>& particleSizes,
                                             const vector<double>& particleWeights,
                                             MassRateRatios& ratio) const {
    ratio.nucCond().gasSpeciesRatio(GasSpecies::C2H2) = -MW_C2H2 / (2 * MW_C);
    ratio.nucCond().gasSpeciesRatio(GasSpecies::H2) = MW_H2 / (2 * MW_C);

    const double Rnuc = 0.1E5 * exp(-21100 / state.getT()) * state.getGasSpeciesC(GasSpecies::C2H2);    // kmol/m3*s
    return Rnuc * 2 * Na / state.getCMin();   // #/m3*s
}
