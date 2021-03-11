#ifndef OXIDATIONMODEL_H
#define OXIDATIONMODEL_H

#include "sootlib/state/MomentState.h"
#include "sootlib/MassRateRatio.h"

namespace soot
{
class OxidationModel
{
public:
	[[nodiscard]] virtual double getOxidationRate(const MomentState& state, MassRateRatio& ratio) const = 0;

	virtual ~OxidationModel() = default;
};
}

#endif //OXIDATIONMODEL_H
