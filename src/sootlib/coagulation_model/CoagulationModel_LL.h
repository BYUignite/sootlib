#ifndef COAGULATIONMODEL_LL_H
#define COAGULATIONMODEL_LL_H

#include "sootlib/state/gas/GasState.h"
#include "sootlib/state/soot/MomentSootState.h"
#include "sootlib/coagulation_model/CoagulationModel.h"

namespace soot
{
class CoagulationModel_LL : public CoagulationModel
{
public:
	// TODO implement
	[[nodiscard]] double getCoagulationRate(const GasState& gasState, const MomentSootState& sootState, double m1, double m2) const override;

	~CoagulationModel_LL() override = default;
};
}

#endif //COAGULATIONMODEL_LL_H
