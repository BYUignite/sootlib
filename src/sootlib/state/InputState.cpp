#include "InputState.h"

using namespace std;
using namespace soot;

double InputState::getT() const {
    return T;
}
void InputState::setT(double t) {
    T = t;
}
double InputState::getP() const {
    return P;
}
void InputState::setP(double p) {
    P = p;
}
double InputState::getRhoGas() const {
    return rhoGas;
}
void InputState::setRhoGas(double rhoGas) {
    InputState::rhoGas = rhoGas;
}
double InputState::getMwGas() const {
    return MWGas;
}
void InputState::setMwGas(double mwGas) {
    MWGas = mwGas;
}
double InputState::getMuGas() const {
    return muGas;
}
void InputState::setMuGas(double muGas) {
    InputState::muGas = muGas;
}
double InputState::getGasSpeciesFrac(GasSpecies species, double def) const {
    if (gasFractions.count(species) == 0)
        return def;
    return gasFractions.at(species);
}
void InputState::setGasSpeciesFrac(GasSpecies species, double frac) {
    gasFractions[species] = frac;
}
double InputState::getGasSpeciesC(GasSpecies species, double def) const {
    if (gasFractions.count(species) == 0)
        return def;
    return rhoGas * gasFractions.at(species) / gasSpeciesMW.at(species);
}
double InputState::getGasSpeciesP(GasSpecies species, double def) const {
    if (gasFractions.count(species) == 0)
        return def;
    return gasFractions.at(species) * MWGas / gasSpeciesMW.at(species) * P;
}
double InputState::getPAHFrac(size_t n, double def) const {
    if (PAHFractions.count(n) == 0)
        return def;
    return PAHFractions.at(n);
}
void InputState::setPAHFrac(size_t n, double frac) {
    PAHFractions[n] = frac;
}
double InputState::getPAHC(size_t n, double def) const {
    if (PAHFractions.count(n) == 0)
        return def;
    return rhoGas * PAHFractions.at(n) / PAH_MW(n);
}
double InputState::getPAHP(size_t n, double def) const {
    if (PAHFractions.count(n) == 0)
        return def;
    return PAHFractions.at(n) * MWGas / PAH_MW(n) * P;
}
double InputState::getGasMeanFreePath() const {
    return muGas / rhoGas * sqrt(M_PI * MWGas / (2.0 * Rg * T));
}
double InputState::getRhoSoot() const {
    return rhoSoot;
}
void InputState::setRhoSoot(double rho) {
    rhoSoot = rho;
}
double InputState::getCMin() {
    if (!mDimerValid)
        calculateMDimer();
    return cMin;
}
double InputState::getDimer() const {
    return dimer;
}
void InputState::setDimer(double dimer) {
    InputState::dimer = dimer;
}
void InputState::calculateMDimer(MassRateRatios* ratio) {
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
            ratio->nucCond().PAHSpeciesRatio(n) = wDotI * MPAHn;
    }

    if (ratio != nullptr) {
        for (const auto&[n, frac] : PAHFractions)
            ratio->nucCond().PAHSpeciesRatio(n) /= mDimer;
    }

    mDimer += 2 / wdotD;
    cMin *= 4 / wdotD;

    if (ratio != nullptr) {
        for (const auto&[n, frac] : PAHFractions)
            ratio->nucCond().PAHSpeciesRatio(n) *= -2 * mDimer / (cMin * MW_C / Na);
    }
    ratio->nucCond().gasSpeciesRatio(GasSpecies::H2) = 2 * mDimer / (cMin * MW_C / Na) - 1;

    mDimerValid = true;
}
double InputState::getNi(size_t i) const {
    return rhoGas * PAHFractions.at(i) / PAH_MW(i) * Na;
}
double InputState::getGammai(size_t i) const {
    const double m_PAH = PAH_MW(i) / Na;
    return m_PAH > 153 ? 1.501E-11 * pow(m_PAH, 4) : 1.501E-11 * pow(m_PAH, 4) / 3.0;
}
double InputState::getMDimer() {
    if (!mDimerValid)
        calculateMDimer();
    return mDimer;
}
double InputState::getWDotD() {
    if (!mDimerValid)
        calculateMDimer();
    return wdotD;
}
map<GasSpecies, double>::const_iterator InputState::gasFractionsBegin() const {
    return gasFractions.begin();
}
map<GasSpecies, double>::const_iterator InputState::gasFractionsEnd() const {
    return gasFractions.end();
}
map<size_t, double>::const_iterator InputState::PAHFractionsBegin() const {
    return PAHFractions.begin();
}
map<size_t, double>::const_iterator InputState::PAHFractionsEnd() const {
    return PAHFractions.end();
}
size_t InputState::getNumBins() const {
    return bins.size();
}
void InputState::resetBins(size_t numBins) {
    bins = vector<double>(numBins, 0);
}
double InputState::getBin(size_t i) const {
    return bins.at(i);
}
void InputState::setBin(size_t i, double value) {
    bins.at(i) = value;
}
std::vector<double>& InputState::getBins() {
    return bins;
}
size_t InputState::getNumMoments() const {
    return moments.size();
}
void InputState::resetMoments(size_t numMoments) {
    moments = vector<double>(numMoments, 0);
}
double InputState::getMoment(size_t i) const {
    return moments.at(i);
}
void InputState::setMoment(size_t i, double value) {
    moments.at(i) = value;
}
std::vector<double>& InputState::getMoments() {
    return moments;
}
