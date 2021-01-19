#include "GasStateFactory.h"
int soot::GasStateFactory::findGasSpIndex(std::string Sp, const std::vector<std::string>& spNames)
{
	std::transform(Sp.begin(), Sp.end(), Sp.begin(), ::toupper);
	int val = std::find(spNames.begin(), spNames.end(), Sp) - spNames.begin();
	if (val == spNames.size())
	{
		std::transform(Sp.begin(), Sp.end(), Sp.begin(), ::tolower);
		val = std::find(spNames.begin(), spNames.end(), Sp) - spNames.begin();
	}
	return (val == spNames.size()) ? -1 : val;
}
soot::GasState soot::GasStateFactory::getGasState() const
{
	if (spNames.size() != PAHspNames.size()
	|| spNames.size() != ncPAH.size()
	|| spNames.size() != MWsp.size()
	|| spNames.size() != gasMoleFractions.size())
	{
		throw std::invalid_argument("Not all property vectors provided to GasState had same length");
	}

	if (gasTemperature == initialVal)
		throw std::invalid_argument("Gas temperature not set");

	if (gasPressure == initialVal)
		throw std::invalid_argument("Gas pressure not set");

	if (gasDensity == initialVal)
		throw std::invalid_argument("Gas density not set");

	if (gasMeanMolecularWeight == initialVal)
		throw std::invalid_argument("Gas mean molecular weight not set");

	if (gasViscosity == initialVal)
		throw std::invalid_argument("Gas viscosity not set");

	return GasState::getInstance(gasTemperature,
							  gasPressure,
							  gasDensity,
							  gasMeanMolecularWeight,
							  gasViscosity,
							  gasMoleFractions,
							  spNames,
							  PAHspNames,
							  ncPAH,
							  MWsp,
							  findGasSpIndex("c2h2", spNames),
							  findGasSpIndex("o2", spNames),
							  findGasSpIndex("h", spNames),
							  findGasSpIndex("h2", spNames),
							  findGasSpIndex("oh", spNames),
							  findGasSpIndex("h2o", spNames),
							  findGasSpIndex("co", spNames));
}
void soot::GasStateFactory::setGasTemperature(double gasTemperature)
{
	GasStateFactory::gasTemperature = gasTemperature;
}
void soot::GasStateFactory::setGasPressure(double gasPressure)
{
	GasStateFactory::gasPressure = gasPressure;
}
void soot::GasStateFactory::setGasDensity(double gasDensity)
{
	GasStateFactory::gasDensity = gasDensity;
}
void soot::GasStateFactory::setGasMeanMolecularWeight(double gasMeanMolecularWeight)
{
	GasStateFactory::gasMeanMolecularWeight = gasMeanMolecularWeight;
}
void soot::GasStateFactory::setGasViscosity(double gasViscosity)
{
	GasStateFactory::gasViscosity = gasViscosity;
}
void soot::GasStateFactory::setGasMoleFractions(const std::vector<double>& gasMoleFractions)
{
	GasStateFactory::gasMoleFractions = gasMoleFractions;
}
void soot::GasStateFactory::setSpNames(const std::vector<std::string>& spNames)
{
	GasStateFactory::spNames = spNames;
}
void soot::GasStateFactory::setPaHspNames(const std::vector<std::string>& paHspNames)
{
	PAHspNames = paHspNames;
}
void soot::GasStateFactory::setNcPah(const std::vector<int>& ncPah)
{
	ncPAH = ncPah;
}
void soot::GasStateFactory::setMWsp(const std::vector<double>& mWsp)
{
	MWsp = mWsp;
}
