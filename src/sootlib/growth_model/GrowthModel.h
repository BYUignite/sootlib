#ifndef GROWTHMODEL_H
#define GROWTHMODEL_H

#include <sootlib/state/gas/State.h>
#include <sootlib/state/soot/MomentSootState.h>

namespace soot
{
class GrowthModel
{
public:
	[[nodiscard]] virtual double getGrowthRate(const State& gasState, const MomentSootState& sootState) const = 0;

	virtual ~GrowthModel() = default;
};
}

#endif //GROWTHMODEL_H
