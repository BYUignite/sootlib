#ifndef GROWTHMODEL_NONE_H
#define GROWTHMODEL_NONE_H

#include "sootlib/growth_model/GrowthModel.h"

namespace soot
{
class GrowthModel_NONE : public GrowthModel
{
public:
	GrowthModel_NONE() : GrowthModel(GrowthMechanism::NONE) {}

	[[nodiscard]] double getGrowthRate(const MomentState& state) const override
	{
		return 0;
	}

	~GrowthModel_NONE() override = default;
};
}

#endif //GROWTHMODEL_NONE_H
