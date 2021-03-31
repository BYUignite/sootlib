#include "BaseState.h"

using namespace std;
using namespace soot;

double BaseState::getT() const {
    return T;
}
void BaseState::setT(double t) {
    T = t;
}
double BaseState::getP() const {
    return P;
}
void BaseState::setP(double p) {
    P = p;
}
double BaseState::getRhoGas() const {
    return rhoGas;
}
void BaseState::setRhoGas(double rhoGas) {
    BaseState::rhoGas = rhoGas;
}
double BaseState::getMwGas() const {
    return MWGas;
}
void BaseState::setMwGas(double mwGas) {
    MWGas = mwGas;
}
double BaseState::getMuGas() const {
    return muGas;
}
void BaseState::setMuGas(double muGas) {
    BaseState::muGas = muGas;
}
double BaseState::getGasSpeciesFrac(GasSpecies species, double def) const {
    if (gasFractions.count(species) == 0)
        return def;
    return gasFractions.at(species);
}
void BaseState::setGasSpeciesFrac(GasSpecies species, double frac) {
    gasFractions[species] = frac;
}
double BaseState::getGasSpeciesC(GasSpecies species, double def) const {
    if (gasFractions.count(species) == 0)
        return def;
    return rhoGas * gasFractions.at(species) / gasSpeciesMW.at(species);
}
double BaseState::getGasSpeciesP(GasSpecies species, double def) const {
    if (gasFractions.count(species) == 0)
        return def;
    return gasFractions.at(species) * MWGas / gasSpeciesMW.at(species) * P;
}
double BaseState::getPAHFrac(size_t n, double def) const {
    if (PAHFractions.count(n) == 0)
        return def;
    return PAHFractions.at(n);
}
void BaseState::setPAHFrac(size_t n, double frac) {
    PAHFractions[n] = frac;
}
double BaseState::getPAHC(size_t n, double def) const {
    if (PAHFractions.count(n) == 0)
        return def;
    return rhoGas * PAHFractions.at(n) / PAH_MW(n);
}
double BaseState::getPAHP(size_t n, double def) const {
    if (PAHFractions.count(n) == 0)
        return def;
    return PAHFractions.at(n) * MWGas / PAH_MW(n) * P;
}
double BaseState::getGasMeanFreePath() const {
    return muGas / rhoGas * sqrt(M_PI * MWGas / (2.0 * Rg * T));
}
double BaseState::getRhoSoot() const {
    return rhoSoot;
}
void BaseState::setRhoSoot(double rho) {
    rhoSoot = rho;
}
double BaseState::getCMin() {
    if (!mDimerValid)
        calculateMDimer();
    return cMin;
}
double BaseState::getDimer() const {
    return dimer;
}
void BaseState::setDimer(double dimer) {
    BaseState::dimer = dimer;
}
void BaseState::calculateMDimer(MassRateRatio* ratio) {
    const double preFac = sqrt(4 * M_PI * kb * T) * pow(6.0 / (M_PI * rhoSoot), 2.0 / 3.0);

    wdotD = 0;
    mDimer = 0;
    // FIXME this was not in the original code but it really looks like it's correct
    cMin = 0;

    double wDotI;
    double MPAHn;
    double N_n;
    const double exp = 1.0 / 6.0;
    for (const auto&[n, frac] : PAHFractions) {
        MPAHn = PAH_MW(n) / Na;
        N_n = getNi(n);
        wDotI = abs(getGammai(n) * preFac * pow(MPAHn, exp) * N_n * N_n);
        wdotD += wDotI;
        mDimer += wDotI * MPAHn;
        cMin += wDotI * MPAHn;

        if (ratio != nullptr)
            ratio->PAHSpeciesRatio(n) = wDotI * MPAHn;
    }

    if (ratio != nullptr) {
        for (const auto&[n, frac] : PAHFractions)
            ratio->PAHSpeciesRatio(n) /= mDimer;
    }

    mDimer += 2 / wdotD;
    cMin *= 4 / wdotD;

    if (ratio != nullptr) {
        for (const auto&[n, frac] : PAHFractions)
            ratio->PAHSpeciesRatio(n) *= -2 * mDimer / (cMin * MW_C / Na);
    }
    ratio->gasSpeciesRatio(GasSpecies::H2) = 2 * mDimer / (cMin * MW_C / Na) - 1;

    mDimerValid = true;
}
double BaseState::getNi(size_t i) const {
    return rhoGas * PAHFractions.at(i) / PAH_MW(i) * Na;
}
double BaseState::getGammai(size_t i) const {
    const double m_PAH = PAH_MW(i) / Na;
    return m_PAH > 153 ? 1.501E-11 * pow(m_PAH, 4) : 1.501E-11 * pow(m_PAH, 4) / 3.0;
}
double BaseState::getMDimer() {
    if (!mDimerValid)
        calculateMDimer();
    return mDimer;
}
double BaseState::getWDotD() {
    if (!mDimerValid)
        calculateMDimer();
    return wdotD;
}
map<GasSpecies, double>::const_iterator BaseState::gasFractionsBegin() const {
    return gasFractions.begin();
}
map<GasSpecies, double>::const_iterator BaseState::gasFractionsEnd() const {
    return gasFractions.end();
}
map<size_t, double>::const_iterator BaseState::PAHFractionsBegin() const {
    return PAHFractions.begin();
}
map<size_t, double>::const_iterator BaseState::PAHFractionsEnd() const {
    return PAHFractions.end();
}
