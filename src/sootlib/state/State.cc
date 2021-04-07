#include "State.h"

using namespace std;
using namespace soot;

double State::getT() const {
    return T;
}
void State::setT(double t) {
    T = t;
}
double State::getP() const {
    return P;
}
void State::setP(double p) {
    P = p;
}
double State::getRhoGas() const {
    return rhoGas;
}
void State::setRhoGas(double rhoGas) {
    State::rhoGas = rhoGas;
}
double State::getMwGas() const {
    return MWGas;
}
void State::setMwGas(double mwGas) {
    MWGas = mwGas;
}
double State::getMuGas() const {
    return muGas;
}
void State::setMuGas(double muGas) {
    State::muGas = muGas;
}
double State::getGasSpeciesFrac(GasSpecies species, double def) const {
    if (gasFractions.count(species) == 0)
        return def;
    return gasFractions.at(species);
}
void State::setGasSpeciesFrac(GasSpecies species, double frac) {
    gasFractions[species] = frac;
}
double State::getGasSpeciesC(GasSpecies species, double def) const {
    if (gasFractions.count(species) == 0)
        return def;
    return rhoGas * gasFractions.at(species) / gasSpeciesMW.at(species);
}
double State::getGasSpeciesP(GasSpecies species, double def) const {
    if (gasFractions.count(species) == 0)
        return def;
    return gasFractions.at(species) * MWGas / gasSpeciesMW.at(species) * P;
}
double State::getPAHFrac(size_t n, double def) const {
    if (PAHFractions.count(n) == 0)
        return def;
    return PAHFractions.at(n);
}
void State::setPAHFrac(size_t n, double frac) {
    PAHFractions[n] = frac;
}
double State::getPAHC(size_t n, double def) const {
    if (PAHFractions.count(n) == 0)
        return def;
    return rhoGas * PAHFractions.at(n) / PAH_MW(n);
}
double State::getPAHP(size_t n, double def) const {
    if (PAHFractions.count(n) == 0)
        return def;
    return PAHFractions.at(n) * MWGas / PAH_MW(n) * P;
}
double State::getGasMeanFreePath() const {
    return muGas / rhoGas * sqrt(M_PI * MWGas / (2.0 * Rg * T));
}
double State::getRhoSoot() const {
    return rhoSoot;
}
void State::setRhoSoot(double rho) {
    rhoSoot = rho;
}
double State::getCMin() {
    if (!mDimerValid)
        calculateMDimer();
    return cMin;
}
void State::setCMin(double CMin) {
    cMin = CMin;
}
double State::getDimer() const {
    return dimer;
}
void State::setDimer(double dimer) {
    State::dimer = dimer;
}
void State::calculateMDimer(MassRateRatios* ratio) {
    const double preFac = sqrt(4 * M_PI * kb * T) * pow(6.0 / (M_PI * rhoSoot), 2.0 / 3.0);

    wdotD = 0;
    mDimer = 0;
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
double State::getNi(size_t i) const {
    return rhoGas * PAHFractions.at(i) / PAH_MW(i) * Na;
}
double State::getGammai(size_t i) const {
    const double m_PAH = PAH_MW(i) / Na;
    return m_PAH > 153 ? 1.501E-11 * pow(m_PAH, 4) : 1.501E-11 * pow(m_PAH, 4) / 3.0;
}
double State::getMDimer() {
    if (!mDimerValid)
        calculateMDimer();
    return mDimer;
}
double State::getWDotD() {
    if (!mDimerValid)
        calculateMDimer();
    return wdotD;
}
map<GasSpecies, double>::const_iterator State::gasFractionsBegin() const {
    return gasFractions.begin();
}
map<GasSpecies, double>::const_iterator State::gasFractionsEnd() const {
    return gasFractions.end();
}
map<size_t, double>::const_iterator State::PAHFractionsBegin() const {
    return PAHFractions.begin();
}
map<size_t, double>::const_iterator State::PAHFractionsEnd() const {
    return PAHFractions.end();
}
size_t State::getNumBins() const {
    return bins.size();
}
void State::resetBins(size_t numBins) {
    bins = vector<double>(numBins, 0);
}
double State::getBin(size_t i) const {
    return bins.at(i);
}
void State::setBin(size_t i, double value) {
    bins.at(i) = value;
}
std::vector<double>& State::getBins() {
    return bins;
}
size_t State::getNumMoments() const {
    return moments.size();
}
void State::resetMoments(size_t numMoments) {
    moments = vector<double>(numMoments, 0);
}
double State::getMoment(size_t i) const {
    return moments.at(i);
}
void State::setMoment(size_t i, double value) {
    moments.at(i) = value;
}
std::vector<double>& State::getMoments() {
    return moments;
}
const std::vector<double>& State::getBinsConst() const {
    return bins;
}
const std::vector<double>& State::getMomentsConst() const {
    return moments;
}
