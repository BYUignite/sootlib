#ifndef COAGULATIONMODEL_FUCHS_H
#define COAGULATIONMODEL_FUCHS_H

#include "sootlib/state/gas/GasState.h"
#include "sootlib/state/soot/MomentSootState.h"
#include "sootlib/coagulation_model/CoagulationModel.h"

namespace soot
{
class CoagulationModel_FUCHS : public CoagulationModel
{
public:
	[[nodiscard]] double getCoagulationRate(const GasState& gasState, const MomentSootState& sootState, double m1, double m2) const override;

	~CoagulationModel_FUCHS() override = default;
};
}

#endif //COAGULATIONMODEL_FUCHS_H
