#ifndef OXIDATIONMODEL_NONE_H
#define OXIDATIONMODEL_NONE_H

#include "sootlib/state/GasState.h"
#include "sootlib/state/MomentSootState.h"
#include "sootlib/oxidation_model/OxidationModel.h"

namespace soot
{
class OxidationModel_NONE : public OxidationModel
{
public:
	[[nodiscard]] double getOxidationRate(const GasState& gasState, const MomentSootState& sootState) const override
	{
		return 0.0;
	}

	~OxidationModel_NONE() override = default;
};
}

#endif //OXIDATIONMODEL_NONE_H
