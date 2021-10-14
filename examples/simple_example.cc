#include <iostream>

#include "constants.h"
#include "sootModel.h"
#include "state.h"

using namespace std;
using namespace soot;

int main(int argc, char** argv) {

    //---------- set up and create a soot model

    // define soot chemistry mechanisms to be used
    nucleationMech  n = nucleationMech::LL;             // Nucleation: NONE, LL, LIN, PAH
    growthMech      g = growthMech::LL;                 // Surface growth: NONE, LL, LIN, HACA
    oxidationMech   x = oxidationMech::LL;              // Oxidation: NONE, LL, LEE_NEOH, NSC_NEOH, HACA
    coagulationMech c = coagulationMech::LL;            // Coagulation: NONE, LL, FUCHS, FRENK

    // define particle size distribution (PSD) treatment
    psdMech         PSD = psdMech::QMOM;                  // PSD mechanisms: MONO, LOGN, QMOM, MOMIC
    int             N = 6;                              // number of soot moments

    // create sootModel object with desired mechanisms
    sootModel SM = sootModel(PSD, N, n, g, x, c);

    //---------- set up thermodynamic state variables

    // create state object
    state S = state();

    // specify some state variables

    double T = 2100;        // temperature in K
    double P = 101325;      // pressure in Pa
    double rhoGas = 0.1;    // gas density in kg/m^3
    double muGas = 1E-5;    // gas viscosity in Pa*s
    double MWGas = 29;      // gas molar weight in kg/kmol

    vector<double> yGas = {0, 0.01, 0.01, 0.01, 0.02, 0.03, 0.04, 2E-15};     // gas species mass fractions [H, H2, O, O2, OH, H2O, CO, C2H2]
    vector<double> yPAH = {0, 0, 0, 0, 0, 0};                                 // PAH species mass fractions [C10H8, C12H8, C12H10, C14H10, C16H10, C18H10]
    vector<double> ySootVar = {0.003, 1.5E-5, 1E-7, 1E-10};                   // soot moment values [M0, M1, M2, M3]

    // set the thermodynamic state
    S.setState(T, P, rhoGas, muGas, MWGas, yGas, yPAH, ySootVar);

    //---------- calculate source terms

    SM.calcSourceTerms(S);

    //---------- accessing source term results

    // soot source terms
    double S_M0 = SM.sourceTerms->sootSourceTerms.at(0);      // #/m^3*s
    double S_M1 = SM.sourceTerms->sootSourceTerms.at(1);      // kg/m^3*s
    double S_M2 = SM.sourceTerms->sootSourceTerms.at(2);      // kg^2/m^3*s
    double S_M3 = SM.sourceTerms->sootSourceTerms.at(3);      // kg^3/m^3*s

    // gas source terms (kg sp)/(kg gas * s)
    double S_C2H2 = SM.sourceTerms->gasSourceTerms.at(gasSp::C2H2);
    double S_H    = SM.sourceTerms->gasSourceTerms.at(gasSp::H);
    double S_H2   = SM.sourceTerms->gasSourceTerms.at(gasSp::H2);
    double S_O    = SM.sourceTerms->gasSourceTerms.at(gasSp::O);
    double S_O2   = SM.sourceTerms->gasSourceTerms.at(gasSp::O2);
    double S_CO   = SM.sourceTerms->gasSourceTerms.at(gasSp::CO);
    double S_H2O  = SM.sourceTerms->gasSourceTerms.at(gasSp::H2O);
    double S_OH   = SM.sourceTerms->gasSourceTerms.at(gasSp::OH);
    double S_C6H6 = SM.sourceTerms->gasSourceTerms.at(gasSp::C6H6);

    // PAH source terms (kg sp)/(kg gas * s)
    double S_C10H8  = SM.sourceTerms->pahSourceTerms.at(pahSp::C10H8);
    double S_C12H8  = SM.sourceTerms->pahSourceTerms.at(pahSp::C12H8);
    double S_C12H10 = SM.sourceTerms->pahSourceTerms.at(pahSp::C12H10);
    double S_C14H10 = SM.sourceTerms->pahSourceTerms.at(pahSp::C14H10);
    double S_C16H10 = SM.sourceTerms->pahSourceTerms.at(pahSp::C16H10);
    double S_C18H10 = SM.sourceTerms->pahSourceTerms.at(pahSp::C18H10);

    //---------- display results


    return 0;
}