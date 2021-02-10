#ifndef NUCLEATIONMODEL_H
#define NUCLEATIONMODEL_H

#include "sootlib/state/GasState.h"
#include "sootlib/state/MomentSootState.h"

namespace soot
{
class NucleationModel
{
public:
	[[nodiscard]] virtual double getNucleationRate(const GasState& gasState, const MomentSootState& sootState) const = 0;

	virtual ~NucleationModel() = default;
};
}

#endif //NUCLEATIONMODEL_H
