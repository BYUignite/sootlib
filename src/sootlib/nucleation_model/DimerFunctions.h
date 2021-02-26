#ifndef DIMERFUNCTIONS_H
#define DIMERFUNCTIONS_H

#include "sootlib/static.h"
#include "sootlib/state/soot/BaseSootState.h"
#include "sootlib/state/gas/State.h"

namespace soot
{
class DimerFunctions
{
public:
	[[nodiscard]] static double getDimerSelfCollision(const BaseSootState& sootState, const State& gasState)
	{
		double preFac = sqrt(4 * M_PI * kb * gasState.getT()) * pow(6.0 / (M_PI * sootState.getRho()), 2.0 / 3.0);
		double wDotD = 0; // dimer self collision rate

		double gamma_i; // sticking coefficient
		double pahMass; // PAH species mass per molecule
		double pahMoleculesM3; // PAH species number density units: molecules / m3
		double wDotPah; // temporary variable

		// m_dimer should not be set here
		for (const size_t& PAH : gasState.getPAHSpecies())
		{

		}

		return 0;
	}
};
}

#endif //DIMERFUNCTIONS_H
