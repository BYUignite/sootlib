#ifndef OXIDATIONMODEL_H
#define OXIDATIONMODEL_H

#include "sootlib/state/MomentState.h"
#include "sootlib/MassRateRatio.h"

namespace soot
{
class OxidationModel
{
public:
	explicit OxidationModel(OxidationMechanism mechanism)
	{
		this->mechanism = mechanism;
	}

	[[nodiscard]] virtual double getOxidationRate(const MomentState& state, MassRateRatio& ratio) const = 0;

	virtual ~OxidationModel() = default;

	[[nodiscard]] OxidationMechanism getMechanism() const
	{
		return mechanism;
	}

private:
	OxidationMechanism mechanism;
};
}

#endif //OXIDATIONMODEL_H
