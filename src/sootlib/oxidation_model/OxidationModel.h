#ifndef OXIDATIONMODEL_H
#define OXIDATIONMODEL_H

#include "sootlib/state/GasState.h"
#include "sootlib/state/MomentSootState.h"

namespace soot
{
class OxidationModel
{
public:
	[[nodiscard]] virtual double getOxidationRate(const GasState& gasState, const MomentSootState& sootState) const = 0;

	virtual ~OxidationModel() = default;
};
}

#endif //OXIDATIONMODEL_H
