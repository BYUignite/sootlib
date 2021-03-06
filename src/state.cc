#include "state.h"

using namespace soot;
using namespace std;

state::state() {

    gasFractions = {{gasSp::C2H2, 0},
                    {gasSp::O,    0},
                    {gasSp::O2,   0},
                    {gasSp::H,    0},
                    {gasSp::H2,   0},
                    {gasSp::OH,   0},
                    {gasSp::H2O,  0},
                    {gasSp::CO,   0},
                    {gasSp::C,    0},
                    {gasSp::C6H6, 0}};

    pahFractions = {{pahSp::C10H8,  0},
                    {pahSp::C12H8,  0},
                    {pahSp::C12H10, 0},
                    {pahSp::C14H10, 0},
                    {pahSp::C16H10, 0},
                    {pahSp::C18H10, 0}};

}

void state::setState(double T_, double P_, double rhoGas_, double muGas_, double MWGas_,
                     vector<double> yGas_, vector<double> yPAH_, vector<double> sootVar_, double cMin_) {

    T = T_;
    P = P_;
    rhoGas = rhoGas_;
    muGas = muGas_;
    MWGas = MWGas_;
    cMin = cMin_;

    // soot moments/bins
    for (int i=0; i<sootVar.size(); i++)
        sootVar.push_back(sootVar_[i]);

    // gas species mass fractions
    gasFractions.at(gasSp::H)    = yGas_[0];
    gasFractions.at(gasSp::H2)   = yGas_[1];
    gasFractions.at(gasSp::O)    = yGas_[2];
    gasFractions.at(gasSp::O2)   = yGas_[3];
    gasFractions.at(gasSp::OH)   = yGas_[4];
    gasFractions.at(gasSp::H2O)  = yGas_[5];
    gasFractions.at(gasSp::CO)   = yGas_[6];
    gasFractions.at(gasSp::C2H2) = yGas_[7];

    // PAH mass fractions
    pahFractions.at(pahSp::C10H8)  = yPAH_[0];
    pahFractions.at(pahSp::C12H8)  = yPAH_[1];
    pahFractions.at(pahSp::C12H10) = yPAH_[2];
    pahFractions.at(pahSp::C14H10) = yPAH_[3];
    pahFractions.at(pahSp::C16H10) = yPAH_[4];
    pahFractions.at(pahSp::C18H10) = yPAH_[5];

}

double state::getParticleCollisionRate(double m1, double m2) const {

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

    double beta_12_C = muGas > 0 ? 2 * kb * T / (3 * muGas) * (Cc1 / Dp1 + Cc2 / Dp1) * (Dp1 + Dp2) : 0;

    //------------ return harmonic mean
    return beta_12_FM * beta_12_C / (beta_12_FM + beta_12_C);

}

//void gasState::printInfo(ostream& out) const {
//    out << " === [gasState] ===" << endl;
//    out << "T: " << T << endl;
//    out << "P: " << P << endl;
//    out << "Rho Gas: " << rhoGas << endl;
//    out << "MW Gas: " << MWGas << endl;
//    out << "Mu Gas: " << muGas << endl;
//
//    out << "Gas fractions (" << gasFractions.size() << ")" << endl;
//    for (const auto& [g, f] : gasFractions)
//        out << "Gas " << (int) g << ": " << f << endl;
//}
