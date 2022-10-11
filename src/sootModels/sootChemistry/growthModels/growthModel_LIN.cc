#include "sootModels/sootChemistry/growthModels/growthModel_LIN.h"
#include "constants.h"

using namespace std;
using namespace soot;

growthModel_LIN::growthModel_LIN() {

    growthRxnRatios.at(gasSp::C2H2) = -1;
    growthRxnRatios.at(gasSp::H2)   =  1;
    growthRxnRatios.at(gasSp::C)    =  2;

}

double growthModel_LIN::getGrowthSootRate(const state &state) const {

    return 750.*exp(-12100./state.T)*state.getGasSpC(gasSp::C2H2) * 
           2. * gasSpMW.at(gasSp::C);        // kg_soot/m2*s

}
