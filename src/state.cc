#include "state.h"

#include <numeric>

using namespace soot;
using namespace std;

////////////////////////////////////////////////////////////////////////////////

void state::setState(double T_, double P_, double rhoGas_, double muGas_, double MWGas_,
                     vector<double> yGas_, vector<double> yPah_, vector<double> sootVar_, int nsoot_, double cMin_) {

    //------------ scalar variable values

    if (T_ <= 0) throw domain_error("Unphysical state value input: T");
    else T = T_;

    if (P_ <= 0) throw domain_error("Unphysical state value input: P");
    else P = P_;

    if (rhoGas_ <= 0) throw domain_error("Unphysical state value input: rhoGas");
    else rhoGas = rhoGas_;

    if (muGas_ <= 0) throw domain_error("Unphysical state value input: muGas");
    else muGas = muGas_;

    if (MWGas_ <= 0) throw domain_error("Unphysical state value input: MWGas");
    else MWGas = MWGas_;

    if (cMin_ <= 0) throw domain_error("Unphysical state value input: cMin");
    else cMin = cMin_;

    //------------ soot moments/bins

    nsoot = nsoot_;
    for (double s : sootVar_)
        if (s < 0)
            throw domain_error("Unphysical state value input: negative soot moment(s)");

    sootVar = sootVar_;

    //------------ gas species mass fractions

    for (double y : yGas_) {
        if (y < 0) {
            y = 0;
        }
        if (y > 1)
            throw domain_error("Unphysical state value input: gas species mass fraction > 1.0");
    }

    double yGas_sum = 0;
    for(double y : yGas_)
        yGas_sum += y;
    if (yGas_sum > 1.0)
        throw domain_error("Unphysical state value input: sum of gas species mass fractions greater than one");

    yGas = yGas_;

    //------------ PAH mass fractions

    if (yPah_.size() != (yPah.size()))
        throw domain_error("Invalid input vector size: PAH species mass fractions");

    for (double y : yPah_)
        if (y < 0 || y > 1)
            throw domain_error("Unphysical state value input: PAH species mass fraction(s)");

    double yPAH_sum = 0;
    for(double y :yPah_)
        yPAH_sum += y;
    if (yPAH_sum > 1.0)
        throw domain_error("Unphysical state value input: sum of PAH species mass fractions greater than one");

    yPah = yPah_;

}

////////////////////////////////////////////////////////////////////////////////

