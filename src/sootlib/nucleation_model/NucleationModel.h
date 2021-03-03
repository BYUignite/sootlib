#ifndef NUCLEATIONMODEL_H
#define NUCLEATIONMODEL_H

#include <vector>

#include "sootlib/state/MomentState.h"

namespace soot
{
class NucleationModel
{
public:
	[[nodiscard]] virtual double getNucleationRate(MomentState& state, const std::vector<double>& particleSizes, const std::vector<double>& particleWeights) const = 0;

	virtual ~NucleationModel() = default;
};
}

#endif //NUCLEATIONMODEL_H
