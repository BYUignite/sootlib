#include "GasState.h"
soot::GasState soot::GasState::getInstance(double gasTemperature,
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
{
	return GasState(gasTemperature,
	                gasPressure,
	                gasDensity,
	                gasMeanMolecularWeight,
	                gasViscosity,
	                std::move(gasMoleFractions),
	                std::move(spNames),
	                std::move(paHspNames),
	                std::move(ncPah),
	                std::move(mWsp),
	                c2H2Index,
	                o2Index,
	                hIndex,
	                h2Index,
	                ohIndex,
	                h2OIndex,
	                coIndex);
}
size_t soot::GasState::getNumGasses() const
{
	return numGasses;
}
double soot::GasState::getGasTemperature() const
{
	return gasTemperature;
}
double soot::GasState::getGasPressure() const
{
	return gasPressure;
}
double soot::GasState::getGasDensity() const
{
	return gasDensity;
}
double soot::GasState::getGasMeanMolecularWeight() const
{
	return gasMeanMolecularWeight;
}
double soot::GasState::getGasViscosity() const
{
	return gasViscosity;
}
int soot::GasState::getC2H2Index() const
{
	return c2h2Index;
}
int soot::GasState::getO2Index() const
{
	return o2Index;
}
int soot::GasState::getHIndex() const
{
	return hIndex;
}
int soot::GasState::getH2Index() const
{
	return h2Index;
}
int soot::GasState::getOhIndex() const
{
	return ohIndex;
}
int soot::GasState::getH2OIndex() const
{
	return h2oIndex;
}
int soot::GasState::getCoIndex() const
{
	return coIndex;
}
double soot::GasState::getGasMoleFraction(size_t index) const
{
	return gasMoleFractions.at(index);
}
std::string soot::GasState::getSpName(size_t index) const
{
	return spNames.at(index);
}
std::string soot::GasState::getPaHspName(size_t index) const
{
	return PAHspNames.at(index);
}
double soot::GasState::getNcPah(size_t index) const
{
	return ncPAH.at(index);
}
double soot::GasState::getMWsp(size_t index) const
{
	return MWsp.at(index);
}
