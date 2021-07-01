#include "state.h"

using namespace soot;
using namespace std;

//double state::getGasSpeciesFrac(gasSpecies species, double def) const {
//    return gasFractions.count(species) == 0 ? def : gasFractions.at(species);
//}
//void state::setGasSpeciesFrac(gasSpecies species, double frac) { gasFractions.at(species) = frac; }

double  state::getGasSpeciesC(gasSpecies species, double def) const {
    return gasFractions.count(species) == 0 ? def : rhoGas * gasFractions.at(species) / gasSpeciesMW.at(species);
}

double state::getGasMeanFreePath() const { return muGas / rhoGas * sqrt(M_PI * MWGas / (2.0 * Rg * T)); }

double state::getGasSpeciesP(gasSpecies species, double def) const {
    return gasFractions.count(species) == 0 ? def : gasFractions.at(species) * MWGas / gasSpeciesMW.at(species) * P;
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

//double state::get_PAHFrac(size_t n, double def) const {
//    return pahFractions.count(n) == 0 ? def : pahFractions.at(n);
//}
//void state::set_PAHFrac(size_t n, double frac) { pahFractions[n] = frac; }

double state::get_PAHC(size_t n, double def) const {
    return pahFractions.count(n) == 0 ? def : rhoGas * pahFractions.at(n) / PAH_MW(n);
}
double state::get_PAHP(size_t n, double def) const {
    return pahFractions.count(n) == 0 ? def : pahFractions.at(n) * MWGas / PAH_MW(n) * P;
}

double state::PAH_MW(size_t n) {
    return (double) n * MW_C;
}
double state::getPAHGamma(size_t n) {
    const double m_PAH = PAH_MW(n) / Na;
    return m_PAH > 153 ? 1.501E-11 * pow(m_PAH, 4) : 1.501E-11 * pow(m_PAH, 4) / 3;
}
double state::getPAHN(size_t n) const {
    return rhoGas * pahFractions.at(n) / PAH_MW(n) * Na;
}
