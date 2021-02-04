#ifndef COAGULATIONMODEL_FUCHS_H
#define COAGULATIONMODEL_FUCHS_H

#include "sootlib/coagulation_model/CoagulationModel.h"

namespace soot
{
class CoagulationModel_FUCHS : public CoagulationModel
{
public:
	// TODO implement
	[[nodiscard]] double getCoagulationRate() const override;

	~CoagulationModel_FUCHS() override = default;
};
}

#endif //COAGULATIONMODEL_FUCHS_H
