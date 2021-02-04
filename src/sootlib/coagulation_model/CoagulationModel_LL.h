#ifndef COAGULATIONMODEL_LL_H
#define COAGULATIONMODEL_LL_H

#include <cmath>

#include "sootlib/coagulation_model/CoagulationModel.h"

namespace soot
{
class CoagulationModel_LL : public CoagulationModel
{
public:
	// TODO implement
	[[nodiscard]] double getCoagulationRate() const override;

	~CoagulationModel_LL() override = default;
};
}

#endif //COAGULATIONMODEL_LL_H
