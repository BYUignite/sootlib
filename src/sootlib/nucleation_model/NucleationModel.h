#ifndef NUCLEATIONMODEL_H
#define NUCLEATIONMODEL_H

#include "sootlib/state/GasState.h"
#include "sootlib/state/SootState.h"

namespace soot
{
class NucleationModel
{
public:
	[[nodiscard]] virtual double getNucleationRate(const GasState& gasState, const SootState& sootState) const = 0;

	virtual ~NucleationModel() = default;
};
}

#endif //NUCLEATIONMODEL_H
