#ifndef GROWTHMODEL_NONE_H
#define GROWTHMODEL_NONE_H

#include "sootlib/growth_model/GrowthModel.h"

namespace soot
{
class GrowthModel_NONE : public GrowthModel
{
public:
	[[nodiscard]] double getGrowthRate(const GasState& gasState, const SootState& sootState) const override
	{
		return 0.0;
	}

	~GrowthModel_NONE() override = default;
};
}

#endif //GROWTHMODEL_NONE_H
