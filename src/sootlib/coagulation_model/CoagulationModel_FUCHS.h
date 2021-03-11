#ifndef COAGULATIONMODEL_FUCHS_H
#define COAGULATIONMODEL_FUCHS_H

#include "sootlib/coagulation_model/CoagulationModel.h"

namespace soot
{
class CoagulationModel_FUCHS : public CoagulationModel
{
public:
	CoagulationModel_FUCHS() : CoagulationModel(CoagulationMechanism::FUCHS) {}

	[[nodiscard]] double getCoagulationRate(const MomentState& state, double m1, double m2) const override;

	~CoagulationModel_FUCHS() override = default;
};
}

#endif //COAGULATIONMODEL_FUCHS_H
