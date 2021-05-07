#ifndef STATIC_H
#define STATIC_H

#include <map>

namespace soot {
const double Na = 6.02214086E26;  ///< Avogadro's constant: #/kmol
const double kb = 1.38064852E-23; ///< Boltzmann constant = Rg/Na: J/#*K
const double Rg = 8314.46;        ///< Universal gas constant
const double eps_c = 2.2;            ///< coagulation constant
const double Df = 1.8;            ///< soot fractal dimension

enum class NucleationMechanism { NONE, LL, LIN, PAH };
enum class GrowthMechanism { NONE, LL, LIN, HACA };
enum class OxidationMechanism { NONE, LL, LEE_NEOH, NSC_NEOH, HACA };
enum class CoagulationMechanism { NONE, LL, FUCHS, FRENK };

const double MW_C2H2 = 26.038;
const double MW_O2 = 31.998;
const double MW_H = 1.008;
const double MW_H2 = 2.016;
const double MW_OH = 17.007;
const double MW_H2O = 18.015;
const double MW_CO = 28.010;
const double MW_C = 12.011;

enum class GasSpecies { C2H2, O2, H, H2, OH, H2O, CO, C };

const std::map<GasSpecies, double> gasSpeciesMW = {{GasSpecies::C2H2, MW_C2H2},
                                                   {GasSpecies::O2, MW_O2},
                                                   {GasSpecies::H, MW_H},
                                                   {GasSpecies::H2, MW_H2},
                                                   {GasSpecies::OH, MW_OH},
                                                   {GasSpecies::H2O, MW_H2O},
                                                   {GasSpecies::CO, MW_CO},
                                                   {GasSpecies::C, MW_C}};
}

#endif //STATIC_H
