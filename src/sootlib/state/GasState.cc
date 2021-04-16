#include "GasState.h"

#include <cmath>

using namespace soot;
using namespace std;

double GasState::getRhoGas() const {
    return rhoGas;
}
void GasState::setRhoGas(double rhoGas) {
    GasState::rhoGas = rhoGas;
}
double GasState::getMWGas() const {
    return MWGas;
}
void GasState::setMWGas(double mwGas) {
    MWGas = mwGas;
}
double GasState::getMuGas() const {
    return muGas;
}
void GasState::setMuGas(double muGas) {
    GasState::muGas = muGas;
}
double GasState::getGasSpeciesFrac(GasSpecies species, double def) const {
    return gasFractions.count(species) == 0 ? def : gasFractions.at(species);
}
void GasState::setGasSpeciesFrac(GasSpecies species, double frac) {
    gasFractions[species] = frac;
}
double GasState::getGasSpeciesC(GasSpecies species, double def) const {
    return gasFractions.count(species) == 0 ? def : rhoGas * gasFractions.at(species) / gasSpeciesMW.at(species);
}
map<GasSpecies, double>::const_iterator GasState::gasFractionsBegin() const {
    return gasFractions.begin();
}
map<GasSpecies, double>::const_iterator GasState::gasFractionsEnd() const {
    return gasFractions.end();
}
double GasState::getT() const {
    return T;
}
void GasState::setT(double T) {
    GasState::T = T;
}
double GasState::getP() const {
    return P;
}
void GasState::setP(double P) {
    GasState::P = P;
}
double GasState::getGasMeanFreePath() const {
    return muGas / rhoGas * sqrt(M_PI * MWGas / (2.0 * Rg * T));
}
double GasState::getPAHFrac(size_t n, double def) const {
    return PAHFractions.count(n) == 0 ? def : PAHFractions.at(n);
}
void GasState::setPAHFrac(size_t n, double frac) {
    PAHFractions[n] = frac;
}
double GasState::getPAHC(size_t n, double def) const {
    return PAHFractions.count(n) == 0 ? def : rhoGas * PAHFractions.at(n) / PAH_MW(n);
}
double GasState::getPAHP(size_t n, double def) const {
    return PAHFractions.count(n) == 0 ? def : PAHFractions.at(n) * MWGas / PAH_MW(n) * P;
}
map<size_t, double>::const_iterator GasState::PAHFractionsBegin() const {
    return PAHFractions.begin();
}
map<size_t, double>::const_iterator GasState::PAHFractionsEnd() const {
    return PAHFractions.end();
}
double GasState::PAH_MW(size_t n) {
    return (double) n * MW_C;
}
double GasState::getPAHGamma(size_t n) {
    const double m_PAH = PAH_MW(n) / Na;
    return m_PAH > 153 ? 1.501E-11 * pow(m_PAH, 4) : 1.501E-11 * pow(m_PAH, 4) / 3;
}
double GasState::getPAHN(size_t n) const {
    return rhoGas * PAHFractions.at(n) / PAH_MW(n) * Na;
}
double GasState::getGasSpeciesP(GasSpecies species, double def) const {
    return gasFractions.count(species) == 0 ? def : gasFractions.at(species) * MWGas / gasSpeciesMW.at(species) * P;
}
