#ifndef GROWTHMODEL_LL_H
#define GROWTHMODEL_LL_H

#include <cmath>

#include "sootlib/growth_model/GrowthModel.h"

namespace soot
{
class GrowthModel_LL : public GrowthModel
{
public:
	// TODO implement
	[[nodiscard]] double getGrowthRate(const GasState& gasState, const SootState& sootState) const override;

	~GrowthModel_LL() override = default;
};
}

#endif //GROWTHMODEL_LL_H
