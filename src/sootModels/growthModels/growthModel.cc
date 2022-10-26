#include "sootModels/sootChemistry/growthModels/growthModel.h"
#include "sootDefs.h"

using namespace std;
using namespace soot;

////////////////////////////////////////////////////////////////////////////////

void growthModel::getGrowthGasRates(const state &stt, 
                                    const double &msootDotGrow, 
                                    vector<double> gasSourcesGrow) const {
    // Compute S in: d(rho*y_k)/dt + ... = ... + S
    // kg_k/m3*s (species k)

    for (size_t sp=0; sp<(size_t)gasSp::size; sp++) {
        if(sp == (size_t)gasSp::C) continue;
            gasSourcesGrow[sp] += msootDotGrow * growthRxnRatios[sp] * gasSpMW[sp] /
                                  (growthRxnRatios[(size_t)gasSp::C] * gasSpMW[(size_t)gasSp::C]);
    }
}
