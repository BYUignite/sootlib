#ifndef NUCLEATIONMODEL_H
#define NUCLEATIONMODEL_H

#include <vector>

#include "sootlib/state/MomentState.h"
#include "sootlib/MassRateRatio.h"

namespace soot
{
class NucleationModel
{
public:
	explicit NucleationModel(NucleationMechanism mechanism)
	{
		this->mechanism = mechanism;
	}

	[[nodiscard]] virtual double getNucleationRate(MomentState& state, const std::vector<double>& particleSizes, const std::vector<double>& particleWeights, MassRateRatio& ratio) const = 0;

	virtual ~NucleationModel() = default;

	[[nodiscard]] NucleationMechanism getMechanism() const
	{
		return mechanism;
	}

private:
	NucleationMechanism mechanism;
};
}

#endif //NUCLEATIONMODEL_H
