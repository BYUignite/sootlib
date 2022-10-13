#include <iostream>
#include <iomanip>

#include "sootDefs.h"
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
    coagulationMech c = coagulationMech::FM;            // Coagulation: NONE, LL, FUCHS, FRENK

    // define particle size distribution (PSD) treatment
    psdMech         PSD = psdMech::QMOM;                // PSD mechanisms: MONO, LOGN, QMOM, MOMIC
    int             N = 4;                              // number of soot moments

    // create sootModel object with desired mechanisms
    sootModel SM = sootModel(PSD, N, n, g, x, c);

    //---------- set up thermodynamic state variables

    // create state object
    state S = state(N);

    // specify some state variables

    double T = 2100;        // temperature in K
    double P = 101325;      // pressure in Pa
    double rhoGas = 0.1;    // gas density in kg/m^3
    double muGas = 1E-5;    // gas viscosity in Pa*s
    double MWGas = 29;      // gas molar weight in kg/kmol

    vector<double> yGas = {3E-4, 0.002, 0.001, 0.05, 0.003, 0.07, 0.1, 0.002};  // gas species mass fractions [H, H2, O, O2, OH, H2O, CO, C2H2]
    vector<double> yPAH = {0, 0, 0, 0, 0, 0};                             // PAH species mass fractions [C10H8, C12H8, C12H10, C14H10, C16H10, C18H10]
    vector<double> sootVar = {0.003, 1.5E-5, 1E-7, 1E-10};                // soot moment values [M0, M1, M2, M3]

    // set the thermodynamic state
    S.setState(T, P, rhoGas, muGas, MWGas, yGas, yPAH, sootVar, N);

    //---------- calculate source terms

    SM.setSourceTerms(S);

    //---------- accessing source term results

    // soot source terms
    double S_M0 = SM.sourceTerms->sootSourceTerms[0];      // #/m^3*s
    double S_M1 = SM.sourceTerms->sootSourceTerms[1];      // kg/m^3*s
    double S_M2 = SM.sourceTerms->sootSourceTerms[2];      // kg^2/m^3*s
    double S_M3 = SM.sourceTerms->sootSourceTerms[3];      // kg^3/m^3*s

    // gas source terms (kg sp)/(kg gas * s)
    double S_C2H2 = SM.sourceTerms->gasSourceTerms[gasSp::C2H2];
    double S_H    = SM.sourceTerms->gasSourceTerms[gasSp::H];
    double S_H2   = SM.sourceTerms->gasSourceTerms[gasSp::H2];
    double S_O    = SM.sourceTerms->gasSourceTerms[gasSp::O];
    double S_O2   = SM.sourceTerms->gasSourceTerms[gasSp::O2];
    double S_CO   = SM.sourceTerms->gasSourceTerms[gasSp::CO];
    double S_H2O  = SM.sourceTerms->gasSourceTerms[gasSp::H2O];
    double S_OH   = SM.sourceTerms->gasSourceTerms[gasSp::OH];
    double S_C6H6 = SM.sourceTerms->gasSourceTerms[gasSp::C6H6];

    // PAH source terms (kg sp)/(kg gas * s)
    double S_C10H8  = SM.sourceTerms->pahSourceTerms[pahSp::C10H8];
    double S_C12H8  = SM.sourceTerms->pahSourceTerms[pahSp::C12H8];
    double S_C12H10 = SM.sourceTerms->pahSourceTerms[pahSp::C12H10];
    double S_C14H10 = SM.sourceTerms->pahSourceTerms[pahSp::C14H10];
    double S_C16H10 = SM.sourceTerms->pahSourceTerms[pahSp::C16H10];
    double S_C18H10 = SM.sourceTerms->pahSourceTerms[pahSp::C18H10];

    //---------- output results
    cout << setprecision(2) << fixed;

    cout << endl << "T (K)  = " << setw(14) << T;
    cout << endl << "P (Pa) = " << setw(14) << P;
    cout << endl;

    cout << setprecision(4) << scientific;

    cout << endl << "Soot source terms" << endl;
    cout << endl << "M0 = " << setw(14) << S_M0;
    cout << endl << "M1 = " << setw(14) << S_M1;
    cout << endl << "M2 = " << setw(14) << S_M2;
    cout << endl << "M3 = " << setw(14) << S_M3;
    cout << endl;

    cout << endl << "Gas source terms" << endl;
    cout << endl << "xC2H2 = " << setw(14) << S_C2H2;
    cout << endl << "xH    = " << setw(14) << S_H;
    cout << endl << "xH2   = " << setw(14) << S_H2;
    cout << endl << "xO    = " << setw(14) << S_O;
    cout << endl << "xO2   = " << setw(14) << S_O2;
    cout << endl << "xCO   = " << setw(14) << S_CO;
    cout << endl << "xH2O  = " << setw(14) << S_H2O;
    cout << endl << "xOH   = " << setw(14) << S_OH;
    cout << endl;

    if(n==nucleationMech::PAH){
        cout << endl << "PAH source terms" << endl;
        cout << endl << "xC10H8  = " << setw(14) << S_C10H8 ;
        cout << endl << "xC12H8  = " << setw(14) << S_C12H8 ;
        cout << endl << "xC12H10 = " << setw(14) << S_C12H10;
        cout << endl << "xC14H10 = " << setw(14) << S_C14H10;
        cout << endl << "xC16H10 = " << setw(14) << S_C16H10;
        cout << endl << "xC18H10 = " << setw(14) << S_C18H10;
        cout << endl;
    }

    //-----------------

    return 0;
}
