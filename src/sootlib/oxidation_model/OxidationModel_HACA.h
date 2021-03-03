#ifndef OXIDATIONMODEL_HACA_H
#define OXIDATIONMODEL_HACA_H

#include "sootlib/oxidation_model/OxidationModel.h"

namespace soot
{
class OxidationModel_HACA : public OxidationModel
{
public:
	[[nodiscard]] double getOxidationRate(const MomentState& state) const override;

	~OxidationModel_HACA() override = default;
};
}

#endif //OXIDATIONMODEL_HACA_H
