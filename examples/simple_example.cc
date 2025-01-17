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

    size_t nsoot = 2;  // 3; etc.
    //size_t Ntar  = 0;

    sootModel_MONO SM(nsoot, nucl, grow, oxid, coag);
    //sootModel_LOGN SM(nsoot, nucl, grow, oxid, coag);

    SM.coag->set_FM_multiplier(9.0/2.0/2.2);

    //---------- set up thermodynamic state variables

    state S = state(nsoot);

    double T      = 2100;    // temperature in K
    double P      = 101325;  // pressure in Pa
    double rhoGas = 0.1;     // gas density in kg/m^3
    double muGas  = 0.00001;    // gas viscosity in Pa*s

    vector<double> yGas{0.05, 0.001, 0.002, 3E-4, 0.003, 0.07, 0.1, 0.002, .18};  // gas species mass fractions [O2, O, H2, H, OH, H2O, CO, C2H2, CO2]
    vector<double> yPAH{0, 0, 0, 0, 0, 0};                                   // PAH species mass fractions [C10H8, C12H8, C12H10, C14H10, C16H10, C18H10]
    //vector<double> yTar{0.001 ,0.02, 0.04, 0.0002};                                     // Tar species mass fractions
    vector<double> Msoot{0.003, 1.5E-5};                        // soot moment values [M0, M1, M2, M3]
    vector<double> Mtar{0.0001};                                             // tar moment values
    S.setState(T, P, rhoGas, muGas, yGas, yPAH, Msoot, nsoot);
    // For biomass fuels
    //vector<double> yBios{0.12, 0.1, 0.6, 0.09, 0.09};                                      // Biomass species mass fractions
    //S.getyBio(yBios);
    //S.get_mtar_ytar();

    // For coal 
    //S.get_coal(.1, .7, 68.2);
    //S.get_mtar_ytar_coal();

    //---------- calculate source terms

    SM.setSourceTerms(S);
    //---------- output results

    cout << setprecision(2) << fixed;

    cout << endl << "T (K)  = " << setw(14) << T;
    cout << endl << "P (Pa) = " << setw(14) << P;

    cout << setprecision(4) << scientific;

    cout << endl << "M0     = " << setw(14) << Msoot[0];
    cout << endl << "M1     = " << setw(14) << Msoot[1];
    //cout << endl << "M2     = " << setw(14) << Msoot[2];
    //cout << endl << "M3     = " << setw(14) << Msoot[3];
    cout << endl;

    cout << endl << "Soot source terms" << endl;
    cout << endl << "M0 = " << setw(14) << SM.sources.sootSources[0];
    cout << endl << "M1 = " << setw(14) << SM.sources.sootSources[1];
    //cout << endl << "M2 = " << setw(14) << SM.sources.sootSources[2];
    //cout << endl << "M3 = " << setw(14) << SM.sources.sootSources[3];
    cout << endl;

    cout << endl << "Gas source terms" << endl;
    cout << endl << "xO2   = " << setw(14) << SM.sources.gasSources[(size_t)gasSp::O2];
    cout << endl << "xO    = " << setw(14) << SM.sources.gasSources[(size_t)gasSp::O];
    cout << endl << "xH2   = " << setw(14) << SM.sources.gasSources[(size_t)gasSp::H2];
    cout << endl << "xH    = " << setw(14) << SM.sources.gasSources[(size_t)gasSp::H];
    cout << endl << "xOH   = " << setw(14) << SM.sources.gasSources[(size_t)gasSp::OH];
    cout << endl << "xH2O  = " << setw(14) << SM.sources.gasSources[(size_t)gasSp::H2O];
    cout << endl << "xCO   = " << setw(14) << SM.sources.gasSources[(size_t)gasSp::CO];
    cout << endl << "xC2H2 = " << setw(14) << SM.sources.gasSources[(size_t)gasSp::C2H2];
    cout << endl << "xC6H6 = " << setw(14) << SM.sources.gasSources[(size_t)gasSp::C6H6];
    cout << endl << "xCO2  = " << setw(14) << SM.sources.gasSources[(size_t)gasSp::CO2];
    cout << endl;

    if (nucl->mechType==nucleationMech::PAH) {
        cout << endl << "PAH source terms" << endl;
        cout << endl << "xC10H8  = " << setw(14) << SM.sources.pahSources[(size_t)pahSp::C10H8];
        cout << endl << "xC12H8  = " << setw(14) << SM.sources.pahSources[(size_t)pahSp::C12H8];
        cout << endl << "xC12H10 = " << setw(14) << SM.sources.pahSources[(size_t)pahSp::C12H10];
        cout << endl << "xC14H10 = " << setw(14) << SM.sources.pahSources[(size_t)pahSp::C14H10];
        cout << endl << "xC16H10 = " << setw(14) << SM.sources.pahSources[(size_t)pahSp::C16H10];
        cout << endl << "xC18H10 = " << setw(14) << SM.sources.pahSources[(size_t)pahSp::C18H10];
        cout << endl;
    }
    
    if (tar->mechType != tarMech::NONE) { 
        cout << endl << "Tar source terms" << endl; 
        cout << endl << "Ntar = " << setw(14) << SM.sources.tarSources[0] << endl;
        
        cout << endl << "Tar gas source terms " << endl;
        cout << endl << "xC6H6O = " << setw(14) << SM.sources.tarGasSources[(size_t)tarSp::C6H6O];
        cout << endl << "xC10H8 = " << setw(14) << SM.sources.tarGasSources[(size_t)tarSp::C10H8];
        cout << endl << "xC7H8  = " << setw(14) << SM.sources.tarGasSources[(size_t)tarSp::C7H8];
        cout << endl << "xC6H6  = " << setw(14) << SM.sources.tarGasSources[(size_t)tarSp::C6H6];
        cout << endl;
    }
    //-----------------

    delete(nucl);
    delete(grow);
    delete(oxid);
    delete(coag);
    delete(tar);

    return 0;
}
