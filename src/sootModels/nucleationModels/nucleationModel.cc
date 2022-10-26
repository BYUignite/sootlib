#include "sootModels/sootChemistry/nucleationModels/nucleationModel.h"
#include "sootDefs.h"

using namespace std;
using namespace soot;

////////////////////////////////////////////////////////////////////////////////

void nucleationModel::getNucleationGasRates(const state &stt, 
                                            const double &msootDotNucl, 
                                            vector<double> gasSourcesNucl) const {
    // Compute S in: d(rho*y_k)/dt + ... = ... + S
    // kg_k/m3*s (species k)

    for (size_t sp=0; sp<(size_t)gasSp::size; sp++) {
        if(sp == (size_t)gasSp::C) continue;
        gasSourcesNucl[sp] += msootDotNucl * nucleationRxnRatios[sp] * gasSpMW[sp] / 
                          (nucleationRxnRatios[(size_t)gasSp::C] * gasSpMW[(size_t)gasSp::C]);
    }
}

