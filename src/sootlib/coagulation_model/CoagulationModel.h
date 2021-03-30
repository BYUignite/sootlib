#ifndef COAGULATIONMODEL_H
#define COAGULATIONMODEL_H

#include "sootlib/state/MomentState.h"

namespace soot
{
class CoagulationModel
{
public:
	[[nodiscard]] virtual double getCoagulationRate(const MomentState& state, double m1, double m2) const = 0;
	[[nodiscard]] virtual CoagulationMechanism getMechanism() const = 0;

	virtual ~CoagulationModel() = default;
};
}

#endif //COAGULATIONMODEL_H
