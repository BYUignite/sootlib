#ifndef COAGULATIONMODEL_FUCHS_H
#define COAGULATIONMODEL_FUCHS_H

#include "sootlib/state/GasState.h"
#include "sootlib/state/MomentSootState.h"
#include "sootlib/coagulation_model/CoagulationModel.h"

namespace soot
{
class CoagulationModel_FUCHS : public CoagulationModel
{
public:
	// TODO implement
	[[nodiscard]] double getCoagulationRate(const GasState& gasState, const MomentSootState& sootState) const override;

	~CoagulationModel_FUCHS() override = default;
};
}

#endif //COAGULATIONMODEL_FUCHS_H
