#ifndef OXIDATIONMODEL_LEE_NEOH_H
#define OXIDATIONMODEL_LEE_NEOH_H

#include "sootlib/oxidation_model/OxidationModel.h"

namespace soot
{
class OxidationModel_LEE_NEOH : public OxidationModel
{
public:
	// TODO implement
	[[nodiscard]] double getOxidationRate() const override;

	~OxidationModel_LEE_NEOH() override = default;
};
}

#endif //OXIDATIONMODEL_LEE_NEOH_H
