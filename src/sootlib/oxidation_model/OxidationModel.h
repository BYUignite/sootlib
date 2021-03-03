#ifndef OXIDATIONMODEL_H
#define OXIDATIONMODEL_H

#include "sootlib/state/MomentState.h"

namespace soot
{
class OxidationModel
{
public:
	[[nodiscard]] virtual double getOxidationRate(const MomentState& state) const = 0;

	virtual ~OxidationModel() = default;
};
}

#endif //OXIDATIONMODEL_H
