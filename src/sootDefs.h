#pragma once

#include <map>
#include <vector>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <memory>
#include <string>

namespace soot {

//////////////////// constants

const double Na = 6.02214076E26;    ///< Avogadro's constant: #/kmol
const double kb = 1.380649E-23;     ///< Boltzmann constant = Rg/Na: J/#*K
const double Rg = Na*kb;            ///< Universal gas constant: J/kmol*K

const double eps_c   = 2.2;         ///< coagulation constant/van der Waals enhancement factor: Harris and Kennedy CST 59:443-454 (1988) https://doi.org/10.1080/00102208808947110
const double Df      = 1.8;         ///< soot fractal dimension
const double rhoSoot = 1850;        ///< soot particle density
const double bCoag   = 0.8536;      ///< coagulation constant, bounded 1/sqrt(2) < bCoag < 1

const double onethird = 1.0/3.0;
const double twothird = 2.0/3.0;
const double root2    = sqrt(2.0);
const double mmin     = 2E-26;      ///< mass of a carbon atom (kg)


//////////////////// mechanism types

enum class nucleationMech { NONE, LL,   LIN, LINA1, PAH,   MB, FAIR, AJ_RED, BROWN,                    size };
enum class growthMech     { NONE, LL,   LIN,        HACA,  MB, FAIR,                                   size };
enum class oxidationMech  { NONE, LL,   LEE_NEOH, MB, FAIR, NSC_NEOH, HACA, AJ_RED, BROWN, OPTJ, OPTG, size };
enum class coagulationMech{ NONE, FM,   CONTINUUM,  HM,       FUCHS,                                   size };
enum class psdMech        { NONE, MONO, LOGN, QMOM, MOMIC,    SECT,                                    size };
enum class tarMech        { NONE, AJ_RED, BROWN,                                                       size };

//////////////////// gas species list and properties

enum class gasSp{ O2, O, H2, H, OH, H2O, CO, C2H2, C6H6, C, CO2, size };

static std::map<std::string, gasSp> gasSpMapSE{{"O2",  gasSp::O2},     ///< map String to Enumeration
                                              {"O" ,  gasSp::O},
                                              {"H2",  gasSp::H2},
                                              {"H",   gasSp::H},
                                              {"OH",  gasSp::OH},
                                              {"H2O", gasSp::H2O},
                                              {"CO",  gasSp::CO},
                                              {"C2H2",gasSp::C2H2},
                                              {"C6H6",gasSp::C6H6},
                                              {"C",   gasSp::C},
                                              {"CO2", gasSp::CO2}};

static std::map<gasSp, std::string> gasSpMapES{{gasSp::O2,  "O2"},     ///< map Enumeration to String
                                              {gasSp::O,   "O" },
                                              {gasSp::H2,  "H2"},
                                              {gasSp::H,   "H"},
                                              {gasSp::OH,  "OH"},
                                              {gasSp::H2O, "H2O"},
                                              {gasSp::CO,  "CO"},
                                              {gasSp::C2H2,"C2H2"},
                                              {gasSp::C6H6,"C6H6"},
                                              {gasSp::C,   "C"},
                                              {gasSp::CO2, "CO2"}};

static std::map<int, std::string> gasSpMapIS{{0,  "O2"},               //< map Int to String
                                            {1,   "O" },
                                            {2,  "H2"},
                                            {3,   "H"},
                                            {4,  "OH"},
                                            {5, "H2O"},
                                            {6,  "CO"},
                                            {7,"C2H2"},
                                            {8,"C6H6"},
                                            {9,   "C"},
                                            {10, "CO2"}};

const std::vector<double> gasSpMW{      ///< (kg/kmol); make sure the order corresponds to the gasSp enum
    31.998,    // O2                    ///< same as in cantera Elements.cpp
    15.999,    // O
    2.016,     // H2
    1.008,     // H
    17.007,    // OH
    18.015,    // H2O
    28.010,    // CO
    26.038,    // C2H2
    78.114,    // C6H6
    12.011,    // C
    44.009     // CO2

};

//////////////////// PAH species list and properties for PAH nucleation and condensation
// See Blanquart & Pitsch (2009) "A joint volume-surface-hydrogen
// multi-variate model for soot formation"

enum class pahSp{ C10H8, C12H8, C12H10, C14H10, C16H10, C18H10, size };

const std::vector<double> pahSpMW = {     ///< (kg/kmol)
    128.174,   // C10H8
    152.196,   // C12H8
    154.212,   // C12H10
    178.234,   // C14H10
    202.256,   // C16H10
    226.278    // C18H10
};

const std::vector<int> pahSpNC = {        ///< # carbon atoms per PAH species
    10,        // C10H8
    12,        // C12H8
    12,        // C12H10
    14,        // C14H10
    16,        // C16H10
    18         // C18H10
};
const std::vector<int> pahSpNH = {        ///< # hydrogen atoms per PAH species
    8,         // C10H8
    8,         // C12H8
    10,        // C12H10
    10,        // C14H10
    10,        // C16H10
    10         // C18H10
};

const std::vector<double> pahSpGamma = {   ///< unitless sticking coefficient
    0.00133,   // C10H8,                   ///< gamma_i = CN*mi^4; CN = 1.5E-11 (fit); gamma_C10H8 = 0.004/3
    0.00267,   // C12H8,                   ///< gamma_C12H8 = 0.008/3 (See Blanquart and Pitsch in Bockhorn 2009
    0.0085,    // C12H10,
    0.0150,    // C14H10,
    0.0250,    // C16H10,
    0.0390     // C18H10,
};

/// Four basic tar types /// 

enum class tarSp{ C6H6O, C10H8, C7H8, C6H6, size};

const std::vector<double> tarSpMW = {
    94.11,   // C6H6O
    128.174, // C10H8
    92.14,   // C7H8
    78.114,  // C6H6

};

/// Four biomass components from CPDbio /// 

enum class bioSp{ cell, hw_hc, sw_hc, hw_lig, sw_lig, size};

static std::map<std::string, bioSp> bioMapSE{{"cell",   bioSp::cell },         // map string to enum
                                             {"hw_hc",  bioSp::hw_hc},
                                             {"sw_hc",  bioSp::sw_hc},
                                             {"hw_lig", bioSp::hw_lig},
                                             {"sw_lig", bioSp::sw_lig}};

static std::map<bioSp, std::string> bioMapES{{bioSp::cell, "cell"},
                                             {bioSp::hw_hc, "hw_hc"},
                                             {bioSp::sw_hc, "sw_sc"},
                                             {bioSp::hw_lig, "hw_lig"},
                                             {bioSp::sw_lig, "sw_lig"}};

static std::map<int, bioSp> bioMapIS{{0, bioSp::cell},
                                     {1, bioSp::hw_hc},
                                     {2, bioSp::sw_hc},
                                     {3, bioSp::hw_lig},
                                     {4, bioSp::sw_lig}};
//////////////////// custom structures

//----------------------

struct dimerStruct {
    double mDimer = 0;
    double nDimer = 0;
    double nDotD  = 0;
};

//----------------------

struct sourceTerms {
    std::vector<double> sootSources;     ///< kg^r/m3*s (moments), or \#/m3*s (sections)
    std::vector<double> gasSources;      ///< kg/m3*s
    std::vector<double> pahSources;      ///< kg/m3*s
    std::vector<double> tarSources;      ///< kg/m3*s 
    std::vector<double> tarGasSources;   ///< kg/m3*s
    

    sourceTerms(size_t nsoot, size_t Ntar) : sootSources(   std::vector<double>(nsoot, 0.0)), 
                                             gasSources(    std::vector<double>((size_t)gasSp::size, 0.0)),
                                             pahSources(    std::vector<double>((size_t)pahSp::size, 0.0)),
                                             tarSources(    std::vector<double>(Ntar, 0.0)), 
                                             tarGasSources( std::vector<double>((size_t)tarSp::size, 0.0)) {}
};

}  // namespace soot
