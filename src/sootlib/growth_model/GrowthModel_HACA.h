#ifndef GROWTHMODEL_HACA_H
#define GROWTHMODEL_HACA_H

#include "sootlib/growth_model/GrowthModel.h"

namespace soot
{
class GrowthModel_HACA : public GrowthModel
{
public:
	[[nodiscard]] double getGrowthRate(const State& gasState, const MomentSootState& sootState) const override;

	~GrowthModel_HACA() override = default;
};
}

#endif //GROWTHMODEL_HACA_H
