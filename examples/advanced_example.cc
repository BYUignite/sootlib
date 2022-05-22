#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

#include "constants.h"
#include "sootModel.h"
#include "state.h"
#include "cantera/base/Solution.h"
#include "cantera/thermo.h"
#include "cantera/transport.h"
#include "cantera/kinetics.h"

//#include "cantera/thermo/IdealGasPhase.h" // defines class IdealGasPhase
//#include "cantera/kinetics/GasKinetics.h"
//#include "cantera/transport.h" // transport properties
//#include <cstdio>

//#include "cantera/zerodim.h"
//#include "cantera/thermo/IdealGasPhase.h"


using namespace std;
using namespace soot;
using namespace Cantera;

int main(int argc, char** argv) {

    //---------- variables setup

    string gases[] = {"H", "H2", "O", "O2", "OH", "H2O", "CO", "C2H2"};
    string PAHs[]  = {"C10H8", "C12H8", "C12H10", "C14H10", "C16H10", "C18H10"};
    map<string, double> yGasSrc = {{"C2H2", 0},
                                   {"O",    0},
                                   {"O2",   0},
                                   {"H",    0},
                                   {"H2",   0},
                                   {"OH",   0},
                                   {"H2O",  0},
                                   {"CO",   0},
                                   {"C",    0},
                                   {"C6H6", 0}};

    double tend = 1.0;
    double tstep = 0.005;
    double tnow = 0.0;

    //---------- cantera setup
    shared_ptr<Solution> gas(newSolution("gri30.yaml","gri30","Mix"));

    //---------- soot model setup

    // define soot chemistry mechanisms to be used
    nucleationMech  n = nucleationMech::LL;             // Nucleation: NONE, LL, LIN, PAH
    growthMech      g = growthMech::LL;                 // Surface growth: NONE, LL, LIN, HACA
    oxidationMech   x = oxidationMech::LL;              // Oxidation: NONE, LL, LEE_NEOH, NSC_NEOH, HACA
    coagulationMech c = coagulationMech::LL;            // Coagulation: NONE, LL, FUCHS, FRENK

    // define particle size distribution (PSD) treatment
    psdMech         PSD = psdMech::MONO;                  // PSD mechanisms: MONO, LOGN, QMOM, MOMIC
    int             N = 2;                              // number of soot moments

    // create sootModel object with desired mechanisms
    sootModel SM = sootModel(PSD, N, n, g, x, c);

    // create state object
    state S = state();

    // soot moment storage
    vector<double> Msoot(N, 0.0);

    //---------- set up output file
    ofstream f_out("soot_example.csv");
    f_out << "time(s), T(K), ";
    for (const auto& sp : gases)
        f_out << "y" << sp << ", ";
    for (int i=0; i<N; i++)
        f_out << "M" << i << ", ";
    f_out << endl;

    //---------- initial conditions
    map<string, double> yGasInit = {{"C2H4", 0.1},     // stoichiometric ethylene/air mixture
                                    {"O2", 0.20},
                                    {"N2", 0.70}};
    gas->thermo()->setState_TPY(298, OneAtm, yGasInit);
    Msoot[0] = 1E6;

    //---------- output initial conditions
    f_out << tnow << ", " << gas->thermo()->temperature() << ", ";
    for (const auto& sp : gases)
        f_out << yGasInit[sp] << ", ";
    for (int i=0; i<N; i++)
        f_out << Msoot[i] << ", ";
    f_out << endl;

    //---------- loop over time
    while (tnow < tend) {
        tnow += tstep;

        // equilibrate via cantera
//        gas->thermo()->equilibrate("TP");
        gas->thermo()->equilibrate("HP");

        // get cantera mass fractions
        vector<double> yGas;
        for (const auto& sp : gases)
            yGas.push_back(gas->thermo()->massFraction(sp));

        vector<double> yPAH(6,0);
        if (n == nucleationMech::PAH) {
            for (const auto& pahSp : PAHs) {
                yPAH.erase(yPAH.begin());                           // remove first vector element
                yPAH.push_back(gas->thermo()->massFraction(pahSp));   // add PAH mass fraction to end of vector
            }
        }

        // calculate soot source terms
        S.setState(gas->thermo()->temperature(),
                   gas->thermo()->pressure(),
                   gas->thermo()->density(),
                   gas->transport()->viscosity(),
                   gas->thermo()->meanMolecularWeight(),
                   yGas, yPAH, Msoot, N);

        SM.calcSourceTerms(S);

        //---------- apply soot source terms
        for (int m=0; m<N; m++)
            Msoot[m] += SM.sourceTerms->sootSourceTerms[m];

        //---------- apply gas source terms from soot reactions
        for (const auto& sp : gases)
            yGasSrc[sp] += SM.sourceTerms->gasSourceTerms[str2gasSp(sp)];

        map<string, double> yGasNew = gas->thermo()->getMassFractionsByName();
        for (const auto& sp : gases)
            yGasNew[sp] += yGasSrc[sp];

        gas->thermo()->setMassFractionsByName(yGasNew);

        //---------- output time step results
        f_out << tnow << ", " << gas->thermo()->temperature() << ", ";
        for (const auto& sp : gases)
            f_out << yGasNew[sp] << ", ";
        for (int i=0; i<N; i++)
            f_out << Msoot[i] << ", ";
        f_out << endl;
    }

    return 0;
}