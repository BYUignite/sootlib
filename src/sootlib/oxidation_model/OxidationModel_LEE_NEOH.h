#ifndef OXIDATIONMODEL_LEE_NEOH_H
#define OXIDATIONMODEL_LEE_NEOH_H

#include "sootlib/oxidation_model/OxidationModel.h"

namespace soot
{
class OxidationModel_LEE_NEOH : public OxidationModel
{
public:
	[[nodiscard]] double getOxidationRate(const MomentState& state, MassRateRatio& ratio) const override;
	[[nodiscard]] OxidationMechanism getMechanism() const override
	{
		return OxidationMechanism::LEE_NEOH;
	}

	~OxidationModel_LEE_NEOH() override = default;
};
}

#endif //OXIDATIONMODEL_LEE_NEOH_H
