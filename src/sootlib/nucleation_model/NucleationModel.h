#ifndef NUCLEATIONMODEL_H
#define NUCLEATIONMODEL_H

#include <vector>

#include "sootlib/state/gas/State.h"
#include "sootlib/state/soot/MomentSootState.h"

namespace soot
{
class NucleationModel
{
public:
	[[nodiscard]] virtual double getNucleationRate(const State& gasState, const MomentSootState& sootState, const std::vector<double>& particleSizes, const std::vector<double>& particleWeights) const = 0;

	virtual ~NucleationModel() = default;
};
}

#endif //NUCLEATIONMODEL_H
