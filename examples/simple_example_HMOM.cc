#include <iostream>
#include <iomanip>

#include "sootHeaders.h"

using namespace std;
using namespace soot;

int main(int argc, char** argv) {

    //---------- set up and create a soot model

    nucleationModel  *nucl = new soot::nucleationModel_LL();
    growthModel      *grow = new soot::growthModel_LL();
    oxidationModel   *oxid = new soot::oxidationModel_LL();
    coagulationModel *coag = new soot::coagulationModel_FM();
    tarModel         *tar  = new soot::tarModel_NONE();

    size_t nsoot = 4; // 3 moments + 1 weight

    sootModel_HMOM SM(nsoot, nucl, grow, oxid, coag);

    SM.coag->set_FM_multiplier(9.0/2.0/2.2);

    //---------- set up thermodynamic state variables

    state S = state(nsoot);

    double T      = 2100;    // temperature in K
    double P      = 101325;  // pressure in Pa
    double rhoGas = 0.1;     // gas density in kg/m^3
    double muGas  = 0.00001; // gas viscosity in Pa*s

    vector<double> yGas{0.05, 0.001, 0.002, 3E-4, 0.003, 0.07, 0.1, 0.002, .18};  // [O2, O, H2, H, OH, H2O, CO, C2H2, CO2]
    vector<double> yPAH{0, 0, 0, 0, 0, 0};                                        // [C10H8, C12H8, C12H10, C14H10, C16H10, C18H10]
    vector<double> Msoot{0.003, 1.5E-5, 1.0E-7, 1.0E-5};                           // [M0, M1, M2, N0]
    S.setState(T, P, rhoGas, muGas, yGas, yPAH, Msoot, nsoot);

    //---------- calculate source terms

    SM.setSourceTerms(S);

    //---------- output results

    cout << setprecision(2) << fixed;

    cout << endl << "T (K)  = " << setw(14) << T;
    cout << endl << "P (Pa) = " << setw(14) << P;

    cout << setprecision(4) << scientific;

    cout << endl << "M0     = " << setw(14) << Msoot[0];
    cout << endl << "M1     = " << setw(14) << Msoot[1];
    cout << endl << "M2     = " << setw(14) << Msoot[2];
    cout << endl << "N0     = " << setw(14) << Msoot[3];
    cout << endl;

    cout << endl << "Soot source terms" << endl;
    cout << endl << "M0 = " << setw(14) << SM.sources.sootSources[0];
    cout << endl << "M1 = " << setw(14) << SM.sources.sootSources[1];
    cout << endl << "M2 = " << setw(14) << SM.sources.sootSources[2];
    cout << endl << "N0 = " << setw(14) << SM.sources.sootSources[3];
    cout << endl;

    //-----------------

    delete(nucl);
    delete(grow);
    delete(oxid);
    delete(coag);
    delete(tar);

    return 0;
}
