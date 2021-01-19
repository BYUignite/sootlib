#ifndef GASSTATEFACTORY_H
#define GASSTATEFACTORY_H

#include <algorithm>
#include <string>
#include <stdexcept>
#include <vector>

#include "GasState.h"

namespace soot
{
class GasStateFactory
{
public:
	[[nodiscard]] GasState getGasState() const;

	void setGasTemperature(double gasTemperature);
	void setGasPressure(double gasPressure);
	void setGasDensity(double gasDensity);
	void setGasMeanMolecularWeight(double gasMeanMolecularWeight);
	void setGasViscosity(double gasViscosity);
	void setGasMoleFractions(const std::vector<double>& gasMoleFractions);
	void setSpNames(const std::vector<std::string>& spNames);
	void setPaHspNames(const std::vector<std::string>& paHspNames);
	void setNcPah(const std::vector<int>& ncPah);
	void setMWsp(const std::vector<double>& mWsp);

private:
	static constexpr double initialVal = -1;

	double gasTemperature = initialVal;
	double gasPressure = initialVal;
	double gasDensity = initialVal;
	double gasMeanMolecularWeight = initialVal;
	double gasViscosity = initialVal;
	std::vector<double> gasMoleFractions;

	std::vector<std::string> spNames;
	std::vector<std::string> PAHspNames;
	std::vector<int> ncPAH;
	std::vector<double> MWsp;

	[[nodiscard]] static int findGasSpIndex(std::string Sp, const std::vector<std::string>& spNames);
};
}

#endif //GASSTATEFACTORY_H
