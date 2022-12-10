#include "growthModels/growthModel.h"
#include "sootDefs.h"

using namespace std;
using namespace soot;

////////////////////////////////////////////////////////////////////////////////
///
/// Gas source terms due to growth for coupling the gas to the soot. 
///
/// @param msootDotGrow   \input  soot growth rate (kg/m3*s)
/// @param gasSourcesGrow \output vector of gas species source terms (kg/m3*s)
///
////////////////////////////////////////////////////////////////////////////////

void growthModel::getGrowthGasRates( const double &msootDotGrow, 
                                    vector<double> &gasSourcesGrow) const {
    // Compute S in: d(rho*y_k)/dt + ... = ... + S
    // kg_k/m3*s (species k)

    for (size_t sp=0; sp<(size_t)gasSp::size; sp++) {
        if(sp == (size_t)gasSp::C) continue;
            gasSourcesGrow[sp] += msootDotGrow * growthRxnRatios[sp] * gasSpMW[sp] /
                                  (growthRxnRatios[(size_t)gasSp::C] * gasSpMW[(size_t)gasSp::C]);
    }
}
