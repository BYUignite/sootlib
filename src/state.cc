#include "state.h"

#include <numeric>

using namespace soot;
using namespace std;

////////////////////////////////////////////////////////////////////////////////

state::state(size_t nsoot_) :
    nsoot(nsoot_), 
    sootVar(vector<double>(nsoot_, 0.0)),
    sootScales(vector<double>(nsoot_, 1.0)),
    absc(vector<double>(nsoot_/2, 0.0)),
    wts(vector<double>(nsoot_/2, 0.0)) {

    yGas = {{gasSp::C2H2, 0},
                    {gasSp::O,    0},
                    {gasSp::O2,   0},
                    {gasSp::H,    0},
                    {gasSp::H2,   0},
                    {gasSp::OH,   0},
                    {gasSp::H2O,  0},
                    {gasSp::CO,   0},
                    {gasSp::C,    0}};

    yPah = {{pahSp::C10H8,  0},
                    {pahSp::C12H8,  0},
                    {pahSp::C12H10, 0},
                    {pahSp::C14H10, 0},
                    {pahSp::C16H10, 0},
                    {pahSp::C18H10, 0}};
}

////////////////////////////////////////////////////////////////////////////////

void state::setState(double T_, double P_, double rhoGas_, double muGas_, double MWGas_,
                     vector<double> yGas_, vector<double> yPAH_, vector<double> sootVar_, int nsoot_, double cMin_) {

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

    if (yGas_.size() != (yGas.size() - 1))
        throw domain_error("Invalid input vector size: gas species mass fractions");

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

    yGas.at(gasSp::H)    = yGas_[0];
    yGas.at(gasSp::H2)   = yGas_[1];
    yGas.at(gasSp::O)    = yGas_[2];
    yGas.at(gasSp::O2)   = yGas_[3];
    yGas.at(gasSp::OH)   = yGas_[4];
    yGas.at(gasSp::H2O)  = yGas_[5];
    yGas.at(gasSp::CO)   = yGas_[6];
    yGas.at(gasSp::C2H2) = yGas_[7];

    //------------ PAH mass fractions

    if (yPAH_.size() != (yPah.size()))
        throw domain_error("Invalid input vector size: PAH species mass fractions");

    for (double y : yPAH_)
        if (y < 0 || y > 1)
            throw domain_error("Unphysical state value input: PAH species mass fraction(s)");

    double yPAH_sum = 0;
    for(double y :yPAH_)
        yPAH_sum += y;
    if (yPAH_sum > 1.0)
        throw domain_error("Unphysical state value input: sum of PAH species mass fractions greater than one");

    yPah.at(pahSp::C10H8)  = yPAH_[0];
    yPah.at(pahSp::C12H8)  = yPAH_[1];
    yPah.at(pahSp::C12H10) = yPAH_[2];
    yPah.at(pahSp::C14H10) = yPAH_[3];
    yPah.at(pahSp::C16H10) = yPAH_[4];
    yPah.at(pahSp::C18H10) = yPAH_[5];

}

////////////////////////////////////////////////////////////////////////////////

