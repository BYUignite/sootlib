#ifndef GROWTHMODEL_LIN_H
#define GROWTHMODEL_LIN_H

#include "sootlib/growth_model/GrowthModel.h"

namespace soot
{
class GrowthModel_LIN : public GrowthModel
{
public:
	// TODO implement
	[[nodiscard]] double getGrowthRate() const override;

	~GrowthModel_LIN() override = default;
};
}

#endif //GROWTHMODEL_LIN_H
