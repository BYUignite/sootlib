#ifndef COAGULATIONMODEL_LL_H
#define COAGULATIONMODEL_LL_H

#include "sootlib/coagulation_model/CoagulationModel.h"

namespace soot
{
class CoagulationModel_LL : public CoagulationModel
{
public:
	[[nodiscard]] double getCoagulationRate(const MomentState& state, double m1, double m2) const override;
	[[nodiscard]] CoagulationMechanism getMechanism() const override
	{
		return CoagulationMechanism::LL;
	}

	~CoagulationModel_LL() override = default;
};
}

#endif //COAGULATIONMODEL_LL_H
