#include "oxidationModels/oxidationModel.h"
#include "sootDefs.h"

using namespace std;
using namespace soot;

////////////////////////////////////////////////////////////////////////////////

void oxidationModel::getOxidationGasRates(const double &msootDotOxid, 
                                          vector<double> &gasSourcesOxid) const {
    // Compute S in: d(rho*y_k)/dt + ... = ... + S
    // kg_k/m3*s (species k)

    for (size_t sp=0; sp<(size_t)gasSp::size; sp++) {
        if(sp == (size_t)gasSp::C) continue;
        gasSourcesOxid[sp] += msootDotOxid * oxidationRxnRatios[sp] * gasSpMW[sp] /
                              (oxidationRxnRatios[(size_t)gasSp::C] * gasSpMW[(size_t)gasSp::C]);
    }
}
