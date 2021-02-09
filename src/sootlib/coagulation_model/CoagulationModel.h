#ifndef COAGULATIONMODEL_H
#define COAGULATIONMODEL_H

#include "sootlib/state/GasState.h"
#include "sootlib/state/SootState.h"

namespace soot
{
class CoagulationModel
{
public:
	[[nodiscard]] virtual double getCoagulationRate(const GasState& gasState, const SootState& sootState) const = 0;

	virtual ~CoagulationModel() = default;
};
}

#endif //COAGULATIONMODEL_H
