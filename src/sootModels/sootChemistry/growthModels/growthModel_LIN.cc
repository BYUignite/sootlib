#include "sootModels/sootChemistry/growthModels/growthModel_LIN.h"
#include "sootDefs.h"

using namespace std;
using namespace soot;

growthModel_LIN::growthModel_LIN() {

    growthRxnRatios[gasSp::C2H2] = -1;
    growthRxnRatios[gasSp::H2]   =  1;
    growthRxnRatios[gasSp::C]    =  2;

    mechType = growthMech::LIN;
}

double growthModel_LIN::getGrowthSootRate(const state &state) const {

    return 750.*exp(-12100./state.T)*state.getGasSpC(gasSp::C2H2) * 
           2. * gasSpMW[(int)gasSp::C];        // kg_soot/m2*s

}
