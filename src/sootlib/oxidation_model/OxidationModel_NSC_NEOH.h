#ifndef OXIDATIONMODEL_NSC_NEOH_H
#define OXIDATIONMODEL_NSC_NEOH_H

#include "sootlib/oxidation_model/OxidationModel.h"

namespace soot
{
class OxidationModel_NSC_NEOH : public OxidationModel
{
public:
	OxidationModel_NSC_NEOH() : OxidationModel(OxidationMechanism::NSC_NEOH) {}

	[[nodiscard]] double getOxidationRate(const MomentState& state, MassRateRatio& ratio) const override;

	~OxidationModel_NSC_NEOH() override = default;
};
}

#endif //OXIDATIONMODEL_NSC_NEOH_H
