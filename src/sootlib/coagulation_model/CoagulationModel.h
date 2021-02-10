#ifndef COAGULATIONMODEL_H
#define COAGULATIONMODEL_H

#include "sootlib/state/GasState.h"
#include "sootlib/state/MomentSootState.h"

namespace soot
{
class CoagulationModel
{
public:
	[[nodiscard]] virtual double getCoagulationRate(const GasState& gasState, const MomentSootState& sootState) const = 0;

	virtual ~CoagulationModel() = default;
};
}

#endif //COAGULATIONMODEL_H
