#ifndef OXIDATIONMODEL_LL_H
#define OXIDATIONMODEL_LL_H

#include "sootlib/state/gas/State.h"
#include "sootlib/state/soot/MomentSootState.h"
#include "sootlib/oxidation_model/OxidationModel.h"

namespace soot
{
class OxidationModel_LL : public OxidationModel
{
public:
	// TODO implement
	[[nodiscard]] double getOxidationRate(const State& gasState, const MomentSootState& sootState) const override;

	~OxidationModel_LL() override = default;
};
}

#endif //OXIDATIONMODEL_LL_H
