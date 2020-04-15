
#include <iostream>
#include <vector>
#include <string>
#include "../src/soot_MONO.h"
#include "cantera/IdealGasMix.h"
#include "cantera/transport.h"

using namespace std;
using namespace Cantera;

//////////////////////////////////////////////////////////////

int main(){

    IdealGasMix gas("GRI30.xml");
    Transport *tran = newTransportMgr("Mix", &gas);
    cout << endl << "testing soot" << endl;

    int nsvar = 2;
    vector<string> spNames = gas.speciesNames();
    vector<string> PAH_spNames;
    vector<int> nC_PAH;
    vector<double> MW_sp = gas.molecularWeights();
    int Cmin = 100;
    double rhoSoot = 1800;
    string nucleation_mech = "LL";
    string growth_mech = "LIN";
    string oxidation_mech = "NSC_NEOH";
    string coagulation_mech = "FUCHS";

    soot *st;

    st = new soot_MONO(nsvar, spNames, PAH_spNames, nC_PAH, MW_sp, Cmin, rhoSoot, 
                   nucleation_mech, growth_mech, oxidation_mech, coagulation_mech);

    vector<double> y(gas.nSpecies(), 0.0);
    y[gas.speciesIndex("C2H2")] = 0.1;
    y[gas.speciesIndex("N2")] = 0.9;
    gas.setState_TPY(1500, 101325, &y[0]);

    vector<double> yc(gas.nSpecies());
    gas.getMassFractions(&yc[0]);

    cout << endl 
        << gas.temperature() << " " 
        << gas.pressure() << " " 
        << gas.density() <<  " " 
        << gas.meanMolecularWeight() << " "
        << tran->viscosity() << " " 
        << yc[0];
         

    st->set_gas_state_vars(gas.temperature(), gas.pressure(),
                           gas.density(), gas.meanMolecularWeight(),
                           tran->viscosity(), yc);

    st->sootvar[0] = 1.53E16;
    st->sootvar[1] = 0.00185;

    st->setSrc();
    
    cout << endl << st->src[0] << " " << st->src[1];

    return 0;
}
