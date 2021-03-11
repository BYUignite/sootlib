#ifndef OXIDATIONMODEL_LL_H
#define OXIDATIONMODEL_LL_H

#include "sootlib/oxidation_model/OxidationModel.h"

namespace soot
{
class OxidationModel_LL : public OxidationModel
{
public:
	OxidationModel_LL() : OxidationModel(OxidationMechanism::LL) {}

	[[nodiscard]] double getOxidationRate(const MomentState& state, MassRateRatio& ratio) const override;

	~OxidationModel_LL() override = default;
};
}

#endif //OXIDATIONMODEL_LL_H
