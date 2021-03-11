#ifndef MASSRATERATIO_H
#define MASSRATERATIO_H

#include <map>

#include "static.h"

namespace soot
{
class MassRateRatio
{
public:
	double& gasSpeciesRatio(GasSpecies species)
	{
		if (gasSpeciesRatios.count(species) == 0)
			gasSpeciesRatios[species] = 0;
		return gasSpeciesRatios[species];
	}
	double& PAHSpeciesRatio(size_t n)
	{
		if (PAHRatios.count(n) == 0)
			PAHRatios[n] = 0;
		return PAHRatios[n];
	}

	[[nodiscard]] std::map<GasSpecies, double>::const_iterator gasSpeciesBegin() const
	{
		return gasSpeciesRatios.begin();
	}
	[[nodiscard]] std::map<size_t, double>::const_iterator PAHBegin() const
	{
		return PAHRatios.begin();
	}
	[[nodiscard]] std::map<GasSpecies, double>::const_iterator gasSpeciesEnd() const
	{
		return gasSpeciesRatios.end();
	}
	[[nodiscard]] std::map<size_t, double>::const_iterator PAHEnd() const
	{
		return PAHRatios.end();
	}

private:
	std::map<GasSpecies, double> gasSpeciesRatios;
	std::map<size_t, double> PAHRatios;
};
}

#endif //MASSRATERATIO_H
