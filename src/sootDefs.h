#pragma once

#include <map>
#include <vector>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <memory>

namespace soot {

//////////////////// constants

const double Na = 6.02214076E26;    ///< Avogadro's constant: #/kmol
const double kb = 1.380649E-23;     ///< Boltzmann constant = Rg/Na: J/#*K
const double Rg = Na*kb;            ///< Universal gas constant

const double eps_c   = 2.2;         ///< coagulation constant/van der Waals enhancement factor: Harris and Kennedy CST 59:443-454 (1988) https://doi.org/10.1080/00102208808947110
const double Df      = 1.8;         ///< soot fractal dimension
const double rhoSoot = 1850;        ///< soot particle density
const double bCoag   = 0.8536;      ///< coagulation constant, bounded 1/sqrt(2) < bCoag < 1

const double onethird = 1.0/3.0;
const double twothird = 2.0/3.0;
const double root2    = sqrt(2.0);
const double mmin     = 2E-26;      ///< mass of a carbon atom (kg)

//////////////////// mechanism types

enum class nucleationMech { NONE, LL,   LIN,        PAH,             size };
enum class growthMech     { NONE, LL,   LIN,        HACA,            size };
enum class oxidationMech  { NONE, LL,   LEE_NEOH,   NSC_NEOH, HACA,  size };
enum class coagulationMech{ NONE, FM,   CONTINUUM,  HM,       FUCHS, size };
enum class psdMech        { NONE, MONO, LOGN, QMOM, MOMIC,    SECT,  size };

//////////////////// gas species list and properties

enum class gasSp{ O2, O, H2, H, OH, H2O, CO, C2H2, C6H6, C, size };

const std::vector<double> gasSpMW{      // (kg/kmol); make sure the order corresponds to the gasSp enum
    31.998,    // O2
    15.999,    // O
    2.016,     // H2
    1.008,     // H
    17.007,    // OH
    18.015,    // H2O
    28.010,    // CO
    26.038,    // C2H2
    78.114,    // C6H6
    12.011     // C
};

//////////////////// PAH species list and properties for PAH nucleation and condensation
// See Blanquart & Pitsch (2009) "A joint volume-surface-hydrogen
// multi-variate model for soot formation"

enum class pahSp{ C10H8, C12H8, C12H10, C14H10, C16H10, C18H10, size };

const std::vector<double> pahSpMW = {     // (kg/kmol)
    128.173,   // C10H8
    152.195,   // C12H8
    154.211,   // C12H10
    178.233,   // C14H10
    202.255,   // C16H10
    226.277    // C18H10
};

const std::map<pahSp, int> pahSpNC = {{pahSp::C10H8,  10},      ///< number of carbon atoms per PAH species
                                      {pahSp::C12H8,  12},
                                      {pahSp::C12H10, 12},
                                      {pahSp::C14H10, 14},
                                      {pahSp::C16H10, 16},
                                      {pahSp::C18H10, 18}};

const std::map<pahSp, double> pahSpGamma = {{pahSp::C10H8,  0.0010},      ///< unitless sticking coefficient
                                            {pahSp::C12H8,  0.0030},
                                            {pahSp::C12H10, 0.0085},
                                            {pahSp::C14H10, 0.0150},
                                            {pahSp::C16H10, 0.0250},
                                            {pahSp::C18H10, 0.0390}};

//////////////////// custom structures

struct sourceTermStruct {

    std::vector<double>     sootSourceTerms{0, 0};      // default to 2 moments
    std::map<gasSp, double> gasSourceTerms = {{gasSp::C2H2,0},
                                              {gasSp::O,   0},
                                              {gasSp::O2,  0},
                                              {gasSp::H,   0},
                                              {gasSp::H2,  0},
                                              {gasSp::OH,  0},
                                              {gasSp::H2O, 0},
                                              {gasSp::CO,  0},
                                              {gasSp::C,   0},
                                              {gasSp::C6H6,0}};
    std::map<pahSp, double> pahSourceTerms = {{pahSp::C10H8,  0},
                                              {pahSp::C12H8,  0},
                                              {pahSp::C12H10, 0},
                                              {pahSp::C14H10, 0},
                                              {pahSp::C16H10, 0},
                                              {pahSp::C18H10, 0}};
};

//----------------------

struct dimerStruct {
    double mDimer = 0;
    double nDimer = 0;
    double wDotD  = 0;
};

//////////////////// model options and string conversion functions

inline nucleationMech str2nucMech(const std::string& str) {
    if(str == "NONE")     return nucleationMech::NONE;
    else if(str == "LL")  return nucleationMech::LL;
    else if(str == "LIN") return nucleationMech::LIN;
    else if(str == "PAH") return nucleationMech::PAH;
    else throw std::domain_error ("Invalid value provided to str2nucMech function");
}

inline growthMech str2grwMech(const std::string& str) {
    if(str == "NONE")     return growthMech::NONE;
    else if(str == "LL")  return growthMech::LL;
    else if(str == "LIN") return growthMech::LIN;
    else if(str == "HACA") return growthMech::HACA;
    else throw std::domain_error ("Invalid value provided to str2grwMech function");
}

inline oxidationMech str2oxiMech(const std::string& str) {
    if(str == "NONE")           return oxidationMech::NONE;
    else if(str == "LL")        return oxidationMech::LL;
    else if(str == "LEE_NEOH")  return oxidationMech::LEE_NEOH;
    else if(str == "NSC_NEOH")  return oxidationMech::NSC_NEOH;
    else if(str == "HACA")      return oxidationMech::HACA;
    else throw std::domain_error ("Invalid value provided to str2oxiMech function");
}

inline coagulationMech str2coaMech(const std::string& str) {
    if(str == "NONE")           return coagulationMech::NONE;
    else if(str == "FM")        return coagulationMech::FM;
    else if(str == "CONTINUUM") return coagulationMech::CONTINUUM;
    else if(str == "HM")        return coagulationMech::HM;
    else if(str == "FUCHS")     return coagulationMech::FUCHS;
    else throw std::domain_error ("Invalid value provided to str2coaMech function");
}

inline psdMech str2psdMech(const std::string& str) {
    if(str == "NONE")       return psdMech::NONE;
    if(str == "MONO")       return psdMech::MONO;
    else if(str == "LOGN")  return psdMech::LOGN;
    else if(str == "QMOM")  return psdMech::QMOM;
    else if(str == "MOMIC") return psdMech::MOMIC;
    else if(str == "SECT")  return psdMech::SECT;
    else throw std::domain_error ("Invalid value provided to str2psdMech function");
}

inline gasSp str2gasSp(const std::string& str) {
    if(str == "C2H2")       return gasSp::C2H2;
    else if(str == "O")     return gasSp::O;
    else if(str == "O2")    return gasSp::O2;
    else if(str == "H")     return gasSp::H;
    else if(str == "H2")    return gasSp::H2;
    else if(str == "OH")    return gasSp::OH;
    else if(str == "H2O")   return gasSp::H2O;
    else if(str == "CO")    return gasSp::CO;
    else if(str == "C")     return gasSp::C;
    else if(str == "C6H6")  return gasSp::C6H6;
    else throw std::domain_error ("Invalid value provided to str2gasSp function");
}

inline pahSp str2pahSp(const std::string& str) {
    if(str == "C10H8")       return pahSp::C10H8;
    else if(str == "C12H8")  return pahSp::C12H8;
    else if(str == "C12H10") return pahSp::C12H10;
    else if(str == "C14H10") return pahSp::C14H10;
    else if(str == "C16H10") return pahSp::C16H10;
    else if(str == "C18H10") return pahSp::C18H10;
    else throw std::domain_error ("Invalid value provided to str2gasSp function");
}

}  // namespace soot
