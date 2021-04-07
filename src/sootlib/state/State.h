#ifndef BASESTATE_H
#define BASESTATE_H

#include <cmath>
#include <map>

#include "sootlib/static.h"
#include "sootlib/MassRateRatios.h"

namespace soot {
class State {
public:
    [[nodiscard]] double getT() const;
    void setT(double t);
    [[nodiscard]] double getP() const;
    void setP(double p);
    [[nodiscard]] double getRhoGas() const;
    void setRhoGas(double rhoGas);
    [[nodiscard]] double getMwGas() const;
    void setMwGas(double mwGas);
    [[nodiscard]] double getMuGas() const;
    void setMuGas(double muGas);

    [[nodiscard]] double getGasSpeciesFrac(GasSpecies species, double def = 0) const;
    void setGasSpeciesFrac(GasSpecies species, double frac);
    [[nodiscard]] double getGasSpeciesC(GasSpecies species, double def = 0) const;
    [[nodiscard]] double getGasSpeciesP(GasSpecies species, double def = 0) const;

    [[nodiscard]] double getPAHFrac(size_t n, double def = 0) const;
    void setPAHFrac(size_t n, double frac);
    [[nodiscard]] double getPAHC(size_t n, double def = 0) const;
    [[nodiscard]] double getPAHP(size_t n, double def = 0) const;

    [[nodiscard]] double getGasMeanFreePath() const;

    [[nodiscard]] double getRhoSoot() const;
    void setRhoSoot(double rho);
    [[nodiscard]] double getCMin();
    void setCMin(double CMin);
    [[nodiscard]] double getDimer() const;
    void setDimer(double dimer);
    [[nodiscard]] double getMDimer();
    [[nodiscard]] double getWDotD();

    void calculateMDimer(MassRateRatios* ratio = nullptr);

    [[nodiscard]] std::map<GasSpecies, double>::const_iterator gasFractionsBegin() const;
    [[nodiscard]] std::map<GasSpecies, double>::const_iterator gasFractionsEnd() const;
    [[nodiscard]] std::map<size_t, double>::const_iterator PAHFractionsBegin() const;
    [[nodiscard]] std::map<size_t, double>::const_iterator PAHFractionsEnd() const;

    [[nodiscard]] size_t getNumBins() const;
    void resetBins(size_t numBins);
    [[nodiscard]] double getBin(size_t i) const;
    void setBin(size_t i, double value);
    std::vector<double>& getBins();
    [[nodiscard]] const std::vector<double>& getBinsConst() const;

    [[nodiscard]] size_t getNumMoments() const;
    void resetMoments(size_t numMoments);
    [[nodiscard]] double getMoment(size_t i) const;
    void setMoment(size_t i, double value);
    std::vector<double>& getMoments();
    [[nodiscard]] const std::vector<double>& getMomentsConst() const;

private:
    double T = 0;
    double P = 0;
    double rhoGas = 0;
    double MWGas = 0;
    double muGas = 0;

    std::map<GasSpecies, double> gasFractions;
    std::map<size_t, double> PAHFractions;

    double rhoSoot = 1850;
    double cMin = 100;
    double dimer = 0;
    double mDimer = 0;
    double wdotD = 0;

    bool mDimerValid = true;
    [[nodiscard]] double getNi(size_t i) const;
    [[nodiscard]] double getGammai(size_t i) const;

    std::vector<double> bins;
    std::vector<double> moments;
};
}

#endif //BASESTATE_H
