#ifndef COAGULATIONMODEL_FRENK_H
#define COAGULATIONMODEL_FRENK_H

#include "sootlib/state/GasState.h"
#include "sootlib/state/MomentSootState.h"
#include "sootlib/coagulation_model/CoagulationModel.h"

namespace soot
{
class CoagulationModel_FRENK : public CoagulationModel
{
public:
	// TODO implement
	[[nodiscard]] double getCoagulationRate(const GasState& gasState, const MomentSootState& sootState) const override;

	~CoagulationModel_FRENK() override = default;
};
}

#endif //COAGULATIONMODEL_FRENK_H
