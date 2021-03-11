#ifndef COAGULATIONMODEL_H
#define COAGULATIONMODEL_H

#include "sootlib/state/MomentState.h"

namespace soot
{
class CoagulationModel
{
public:
	explicit CoagulationModel(CoagulationMechanism mechanism)
	{
		this->mechanism = mechanism;
	}

	[[nodiscard]] virtual double getCoagulationRate(const MomentState& state, double m1, double m2) const = 0;

	virtual ~CoagulationModel() = default;

	[[nodiscard]] CoagulationMechanism getMechanism() const
	{
		return mechanism;
	}

private:
	CoagulationMechanism mechanism;
};
}

#endif //COAGULATIONMODEL_H
