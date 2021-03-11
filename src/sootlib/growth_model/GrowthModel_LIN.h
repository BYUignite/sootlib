#ifndef GROWTHMODEL_LIN_H
#define GROWTHMODEL_LIN_H

#include "sootlib/growth_model/GrowthModel.h"

namespace soot
{
class GrowthModel_LIN : public GrowthModel
{
public:
	GrowthModel_LIN() : GrowthModel(GrowthMechanism::LL) {}

	[[nodiscard]] double getGrowthRate(const MomentState& state) const override;

	~GrowthModel_LIN() override = default;
};
}

#endif //GROWTHMODEL_LIN_H
