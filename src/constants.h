#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <map>

namespace soot {

    const double Na = 6.02214086E26;    ///< Avogadro's constant: #/kmol
    const double kb = 1.38064852E-23;   ///< Boltzmann constant = Rg/Na: J/#*K
    const double Rg = 8314.46;          ///< Universal gas constant
    const double eps_c = 2.2;           ///< coagulationModel constant
    const double Df = 1.8;              ///< soot fractal dimension
    const double cMin = 100;            ///< soot min num carbon atoms
    const double rhoSoot = 1850;        ///< soot particle density
    const double bCoag = 0.8536;        ///< coagulation constant

    enum class nucleationMech   { NONE, LL, LIN, PAH };
    enum class growthMech       { NONE, LL, LIN, HACA };
    enum class oxidationMech    { NONE, LL, LEE_NEOH, NSC_NEOH, HACA };
    enum class coagulationMech  { NONE, LL, FUCHS, FRENK };
    enum class psdMech          { MONO, LOGN, QMOM, MOMIC, SECT };

    const double MW_C2H2 = 26.038;        ///< molar weight: kg/kmol
    const double MW_O = 15.999;
    const double MW_O2 = 31.998;
    const double MW_H = 1.008;
    const double MW_H2 = 2.016;
    const double MW_OH = 17.007;
    const double MW_H2O = 18.015;
    const double MW_CO = 28.010;
    const double MW_C = 12.011;

    enum class gasSpecies { C2H2, O, O2, H, H2, OH, H2O, CO, C };

    const std::map<gasSpecies, double> gasSpeciesMW = {{gasSpecies::C2H2, MW_C2H2},
                                                       {gasSpecies::O,    MW_O},
                                                       {gasSpecies::O2,   MW_O2},
                                                       {gasSpecies::H,    MW_H},
                                                       {gasSpecies::H2,   MW_H2},
                                                       {gasSpecies::OH,   MW_OH},
                                                       {gasSpecies::H2O,  MW_H2O},
                                                       {gasSpecies::CO,   MW_CO},
                                                       {gasSpecies::C,    MW_C}};


    struct sourceTermStruct {
        std::vector<double>             sootSourceTerms;
        std::map<gasSpecies, double>    gasSourceTerms;
        std::map<size_t, double>        pahSourceTerms;
    };

}

#endif //CONSTANTS_H
