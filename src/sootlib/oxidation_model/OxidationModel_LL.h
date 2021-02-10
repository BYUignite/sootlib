#ifndef OXIDATIONMODEL_LL_H
#define OXIDATIONMODEL_LL_H

#include "sootlib/state/GasState.h"
#include "sootlib/state/MomentSootState.h"
#include "sootlib/oxidation_model/OxidationModel.h"

namespace soot
{
class OxidationModel_LL : public OxidationModel
{
public:
	// TODO implement
	[[nodiscard]] double getOxidationRate(const GasState& gasState, const MomentSootState& sootState) const override;

	~OxidationModel_LL() override = default;
};
}

#endif //OXIDATIONMODEL_LL_H
