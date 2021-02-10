#ifndef COAGULATIONMODEL_NONE_H
#define COAGULATIONMODEL_NONE_H

#include "sootlib/state/GasState.h"
#include "sootlib/state/MomentSootState.h"
#include "sootlib/coagulation_model/CoagulationModel.h"

namespace soot
{
class CoagulationModel_NONE : public CoagulationModel
{
public:
	[[nodiscard]] double getCoagulationRate(const GasState& gasState, const MomentSootState& sootState) const override
	{
		return 0.0;
	}

	~CoagulationModel_NONE() override = default;
};
}

#endif //COAGULATIONMODEL_NONE_H
