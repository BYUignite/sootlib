#include "State.h"

#include <cmath>
#include <ostream>

using namespace std;
using namespace soot;

double State::getCMin() {
    if (!mDimerValid)
        calculateMDimer();
    return cMin;
}
void State::setCMin(double CMin) {
    cMin = CMin;
}
void State::calculateMDimer(MassRateRatios* ratio) {
    const double preFac = sqrt(4 * M_PI * kb * T) * pow(6 / (M_PI * rhoSoot), 2.0 / 3);

    wdotD = 0;
    mDimer = 0;
    cMin = 0;

    double wDotI;
    double MPAHn;
    double N_n;
    const double exp = 1.0 / 6;
    for (const auto& [n, frac] : PAHFractions) {
        MPAHn = PAH_MW(n) / Na;
        N_n = getPAHN(n);
        wDotI = abs(getPAHGamma(n) * preFac * pow(MPAHn, exp) * N_n * N_n);
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
        for (const auto& [n, frac] : PAHFractions)
            ratio->nucCond().PAHSpeciesRatio(n) *= -2 * mDimer / (cMin * MW_C / Na);
        ratio->nucCond().gasSpeciesRatio(GasSpecies::H2) = 2 * mDimer / (cMin * MW_C / Na) - 1;
    }

    mDimerValid = true;
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
void State::setT(double T) {
    mDimerValid = false;
    GasState::setT(T);
}
void State::setRhoSoot(double rhoSoot) {
    mDimerValid = false;
    SootState::setRhoSoot(rhoSoot);
}
void State::setPAHFrac(size_t n, double frac) {
    mDimerValid = false;
    GasState::setPAHFrac(n, frac);
}
void State::printIssues(std::ostream& out) const {
    out << "hi" << std::endl;
}
