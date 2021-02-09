#ifndef GROWTHMODEL_H
#define GROWTHMODEL_H

#include <sootlib/state/GasState.h>
#include <sootlib/state/SootState.h>

namespace soot
{
class GrowthModel
{
public:
	[[nodiscard]] virtual double getGrowthRate(const GasState& gasState, const SootState& sootState) const = 0;

	virtual ~GrowthModel() = default;
};
}

#endif //GROWTHMODEL_H
