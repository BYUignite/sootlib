#ifndef GROWTHMODEL_H
#define GROWTHMODEL_H

#include "sootlib/state/MomentState.h"

namespace soot
{
class GrowthModel
{
public:
	explicit GrowthModel(GrowthMechanism mechanism)
	{
		this->mechanism = mechanism;
	}

	[[nodiscard]] virtual double getGrowthRate(const MomentState& state) const = 0;

	virtual ~GrowthModel() = default;

	[[nodiscard]] GrowthMechanism getMechanism() const
	{
		return mechanism;
	}

private:
	GrowthMechanism mechanism;
};
}

#endif //GROWTHMODEL_H
