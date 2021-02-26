#ifndef COAGULATIONMODEL_H
#define COAGULATIONMODEL_H

#include "sootlib/state/gas/State.h"
#include "sootlib/state/soot/MomentSootState.h"

namespace soot
{
class CoagulationModel
{
public:
	[[nodiscard]] virtual double getCoagulationRate(const State& gasState, const MomentSootState& sootState, double m1, double m2) const = 0;

	virtual ~CoagulationModel() = default;
};
}

#endif //COAGULATIONMODEL_H
