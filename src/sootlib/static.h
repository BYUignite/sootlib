#ifndef STATIC_H
#define STATIC_H

#include <vector>

namespace soot
{
static constexpr double Na    = 6.02214086E26;  ///< Avogadro's constant: #/kmol
static constexpr double kb    = 1.38064852E-23; ///< Boltzmann constant = Rg/Na: J/#*K
static constexpr double Rg    = 8314.46;        ///< Universal gas constant
static constexpr double eps_c = 2.2;            ///< coagulation constant
static constexpr double Df    = 1.8;            ///< soot fractal dimension
static constexpr double MW_c  = 12.011;         ///< mw of carbon
static constexpr double MW_h  = 1.00794;        ///< mw of hydrogen

// TODO add model implementations of the none values
enum class NucleationMechanism {NONE, LL, LIN, PAH};
enum class GrowthMechanism {NONE, LL, LIN, HACA};
enum class OxidationMechanism {NONE, LL, LEE_NEOH, NSC_NEOH, HACA};
enum class CoagulationMechanism {NONE, LL, FUCHS, FRENK};
}

#endif //STATIC_H
