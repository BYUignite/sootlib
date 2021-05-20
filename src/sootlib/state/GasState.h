#ifndef GASSTATE_H_
#define GASSTATE_H_

#include <map>
#include <ostream>

#include "sootlib/constants.h"

namespace soot {
class GasState {
public:
    [[nodiscard]] double getT() const;
    virtual void setT(double T);
    [[nodiscard]] double getP() const;
    void setP(double P);
    [[nodiscard]] double getRhoGas() const;
    void setRhoGas(double rhoGas);
    [[nodiscard]] double getMWGas() const;
    void setMWGas(double mwGas);
    [[nodiscard]] double getMuGas() const;
    void setMuGas(double muGas);

    [[nodiscard]] double getGasSpeciesFrac(GasSpecies species, double def = 0) const;
    void setGasSpeciesFrac(GasSpecies species, double frac);
    [[nodiscard]] double getGasSpeciesC(GasSpecies species, double def = 0) const;
    [[nodiscard]] double getGasSpeciesP(GasSpecies species, double def = 0) const;
    [[nodiscard]] double getGasMeanFreePath() const;

    [[nodiscard]] std::map<GasSpecies, double>::const_iterator gasFractionsBegin() const;
    [[nodiscard]] std::map<GasSpecies, double>::const_iterator gasFractionsEnd() const;

    [[nodiscard]] double getPAHFrac(size_t n, double def = 0) const;
    virtual void setPAHFrac(size_t n, double frac);
    [[nodiscard]] double getPAHC(size_t n, double def = 0) const;
    [[nodiscard]] double getPAHP(size_t n, double def = 0) const;

    [[nodiscard]] std::map<size_t, double>::const_iterator PAHFractionsBegin() const;
    [[nodiscard]] std::map<size_t, double>::const_iterator PAHFractionsEnd() const;

    static double PAH_MW(size_t n);
    static double getPAHGamma(size_t n);
    [[nodiscard]] double getPAHN(size_t n) const;

    void printInfo(std::ostream& out) const;

protected:
    double T = 0;
    double P = 0;
    double rhoGas = 0;
    double MWGas = 0;
    double muGas = 0;

    std::map<GasSpecies, double> gasFractions;
    std::map<size_t, double> PAHFractions;
};
}

#endif //GASSTATE_H_
