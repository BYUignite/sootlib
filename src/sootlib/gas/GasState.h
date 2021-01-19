#ifndef GASSTATE_H
#define GASSTATE_H

#include <string>
#include <utility>
#include <vector>

// TODO all these memebers need their capitalization checked

namespace soot
{
class GasState
{
public:
	[[nodiscard]] static GasState getInstance(double gasTemperature,
	                            double gasPressure,
	                            double gasDensity,
	                            double gasMeanMolecularWeight,
	                            double gasViscosity,
	                            std::vector<double> gasMoleFractions,
	                            std::vector<std::string> spNames,
	                            std::vector<std::string> paHspNames,
	                            std::vector<int> ncPah,
	                            std::vector<double> mWsp,
	                            int c2H2Index,
	                            int o2Index,
	                            int hIndex,
	                            int h2Index,
	                            int ohIndex,
	                            int h2OIndex,
	                            int coIndex);

	[[nodiscard]] size_t getNumGasses() const;
	[[nodiscard]] double getGasTemperature() const;
	[[nodiscard]] double getGasPressure() const;
	[[nodiscard]] double getGasDensity() const;
	[[nodiscard]] double getGasMeanMolecularWeight() const;
	[[nodiscard]] double getGasViscosity() const;
	[[nodiscard]] int getC2H2Index() const;
	[[nodiscard]] int getO2Index() const;
	[[nodiscard]] int getHIndex() const;
	[[nodiscard]] int getH2Index() const;
	[[nodiscard]] int getOhIndex() const;
	[[nodiscard]] int getH2OIndex() const;
	[[nodiscard]] int getCoIndex() const;

	[[nodiscard]] double getGasMoleFraction(size_t index) const;
	[[nodiscard]] std::string getSpName(size_t index) const;
	[[nodiscard]] std::string getPaHspName(size_t index) const;
	[[nodiscard]] double getNcPah(size_t index) const;
	[[nodiscard]] double getMWsp(size_t index) const;

private:
	GasState(double gasTemperature,
	         double gasPressure,
	         double gasDensity,
	         double gasMeanMolecularWeight,
	         double gasViscosity,
	         std::vector<double> gasMoleFractions,
	         std::vector<std::string> spNames,
	         std::vector<std::string> paHspNames,
	         std::vector<int> ncPah,
	         std::vector<double> mWsp,
	         int c2H2Index,
	         int o2Index,
	         int hIndex,
	         int h2Index,
	         int ohIndex,
	         int h2OIndex,
	         int coIndex)
		: numGasses(gasMoleFractions.size()),
		  gasTemperature(gasTemperature),
		  gasPressure(gasPressure),
		  gasDensity(gasDensity),
		  gasMeanMolecularWeight(gasMeanMolecularWeight),
		  gasViscosity(gasViscosity),
		  gasMoleFractions(std::move(gasMoleFractions)),
		  spNames(std::move(spNames)),
		  PAHspNames(std::move(paHspNames)),
		  ncPAH(std::move(ncPah)),
		  MWsp(std::move(mWsp)),
		  c2h2Index(c2H2Index),
		  o2Index(o2Index),
		  hIndex(hIndex),
		  h2Index(h2Index),
		  ohIndex(ohIndex),
		  h2oIndex(h2OIndex),
		  coIndex(coIndex)
	{}

	size_t numGasses;

	double gasTemperature;
	double gasPressure;
	double gasDensity;
	double gasMeanMolecularWeight;
	double gasViscosity;
	std::vector<double> gasMoleFractions;

	std::vector<std::string> spNames;
	std::vector<std::string> PAHspNames;
	std::vector<int> ncPAH;
	std::vector<double> MWsp;

	int c2h2Index;
	int o2Index;
	int hIndex;
	int h2Index;
	int ohIndex;
	int h2oIndex;
	int coIndex;
};
}

#endif //GASSTATE_H
