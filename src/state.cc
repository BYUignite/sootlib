#include "state.h"

#include <numeric>

using namespace soot;
using namespace std;

////////////////////////////////////////////////////////////////////////////////

state::state() {

    gasFractions = {{gasSp::C2H2, 0},
                    {gasSp::O,    0},
                    {gasSp::O2,   0},
                    {gasSp::H,    0},
                    {gasSp::H2,   0},
                    {gasSp::OH,   0},
                    {gasSp::H2O,  0},
                    {gasSp::CO,   0},
                    {gasSp::C,    0}};

    pahFractions = {{pahSp::C10H8,  0},
                    {pahSp::C12H8,  0},
                    {pahSp::C12H10, 0},
                    {pahSp::C14H10, 0},
                    {pahSp::C16H10, 0},
                    {pahSp::C18H10, 0}};

}

////////////////////////////////////////////////////////////////////////////////

void state::setState(double T_, double P_, double rhoGas_, double muGas_, double MWGas_,
                     vector<double> yGas_, vector<double> yPAH_, vector<double> sootVar_, int nMom_, double cMin_) {

    //------------ scalar variable values

    if (T_ <= 0) throw domain_error("Unphysical state value requested: T");
    else T = T_;

    if (P_ <= 0) throw domain_error("Unphysical state value requested: P");
    else P = P_;

    if (rhoGas_ <= 0) throw domain_error("Unphysical state value requested: rhoGas");
    else rhoGas = rhoGas_;

    if (muGas_ <= 0) throw domain_error("Unphysical state value requested: muGas");
    else muGas = muGas_;

    if (MWGas_ <= 0) throw domain_error("Unphysical state value requested: MWGas");
    else MWGas = MWGas_;

    if (cMin_ <= 0) throw domain_error("Unphysical state value requested: cMin");
    else cMin = cMin_;

    //------------ soot moments/bins

    nMom = nMom_;
    for (double s : sootVar_)
        if (s < 0)
            throw domain_error("Unphysical state value requested: negative soot moment value(s)");

    sootMom.resize(nMom);
    absc.resize(nMom/2);
    wts.resize(nMom/2);
    for (int i=0; i<nMom; i++)
        sootMom.at(i) = sootVar_.at(i);

    //------------ gas species mass fractions

    if (yGas_.size() != (gasFractions.size() - 1))
        throw domain_error("Invalid input vector size: gas species mass fractions");

    for (double y : yGas_) {
        if (y < 0) {
            y = 0;
        }
        if (y > 1)
            throw domain_error("Unphysical state value requested: gas species mass fraction > 1.0");
    }

    double yGas_sum = 0;
    for(double y : yGas_)
        yGas_sum += y;
    if (yGas_sum > 1.0)
        throw domain_error("Unphysical state requested: sum of gas species mass fractions greater than one");

    gasFractions.at(gasSp::H)    = yGas_[0];
    gasFractions.at(gasSp::H2)   = yGas_[1];
    gasFractions.at(gasSp::O)    = yGas_[2];
    gasFractions.at(gasSp::O2)   = yGas_[3];
    gasFractions.at(gasSp::OH)   = yGas_[4];
    gasFractions.at(gasSp::H2O)  = yGas_[5];
    gasFractions.at(gasSp::CO)   = yGas_[6];
    gasFractions.at(gasSp::C2H2) = yGas_[7];

    //------------ PAH mass fractions

    if (yPAH_.size() != (pahFractions.size()))
        throw domain_error("Invalid input vector size: PAH species mass fractions");

    for (double y : yPAH_)
        if (y < 0 || y > 1)
            throw domain_error("Unphysical state value requested: PAH species mass fractions");

    double yPAH_sum = 0;
    for(double y :yPAH_)
        yPAH_sum += y;
    if (yPAH_sum > 1.0)
        throw domain_error("Unphysical state requested: sum of PAH species mass fractions greater than one");

    pahFractions.at(pahSp::C10H8)  = yPAH_[0];
    pahFractions.at(pahSp::C12H8)  = yPAH_[1];
    pahFractions.at(pahSp::C12H10) = yPAH_[2];
    pahFractions.at(pahSp::C14H10) = yPAH_[3];
    pahFractions.at(pahSp::C16H10) = yPAH_[4];
    pahFractions.at(pahSp::C18H10) = yPAH_[5];

}

////////////////////////////////////////////////////////////////////////////////

double state::getParticleCollisionRate(double m1, double m2) const {

    if (m1 < 0 || m2 < 0)
        throw domain_error("Unphysical input value in getParticleCollisionRate: m1 and m2 must be greater than zero");
    else if (m1 == 0 || m2 == 0)
        return 0;

    if (isnan(getGasMeanFreePath()))
        throw domain_error("getParticleCollisionRate error: thermodynamic state variables not set");

    double Dp1 = pow(6 * abs(m1) / M_PI / rhoSoot, 1.0 / 3);
    double Dp2 = pow(6 * abs(m2) / M_PI / rhoSoot, 1.0 / 3);

    //------------ free molecular rate
    double m12 = m1+m2 != 0 ? abs(m1 * m2 / (m1 + m2)) : 0;
    double beta_12_FM = eps_c * sqrt(M_PI * kb * T * 0.5 / m12) * pow(Dp1 + Dp2, 2);

    //------------ continuum rate
    double Kn1 = 2 * getGasMeanFreePath() / Dp1;
    double Kn2 = 2 * getGasMeanFreePath() / Dp2;

    double Cc1 = 1 + Kn1 * (1.257 + 0.4 * exp(-1.1 / Kn1));   // Seinfeld p. 372 eq. 9.34. This is for air at 298 K, 1 atm
    double Cc2 = 1 + Kn2 * (1.257 + 0.4 * exp(-1.1 / Kn2));   // for D<<mfp_g, Cc = 1 + 1.657*Kn; Seinfeld p. 380: 10% error at Kn=1, 0% at Kn=0.01, 100

    double beta_12_C = 2 * kb * T / (3 * muGas) * (Cc1 / Dp1 + Cc2 / Dp1) * (Dp1 + Dp2);

    //------------ return harmonic mean
    return beta_12_FM * beta_12_C / (beta_12_FM + beta_12_C);

}