#ifndef COAGULATIONMODEL_FRENK_H
#define COAGULATIONMODEL_FRENK_H

#include "sootlib/coagulation_model/CoagulationModel.h"

namespace soot
{
class CoagulationModel_FRENK : public CoagulationModel
{
public:
	// TODO implement
	[[nodiscard]] double getCoagulationRate() const override;

	~CoagulationModel_FRENK() override = default;
};
}

#endif //COAGULATIONMODEL_FRENK_H
