#ifndef NUCLEATIONMODEL_LL_H
#define NUCLEATIONMODEL_LL_H

#include "sootlib/nucleation_model/NucleationModel.h"

namespace soot
{
class NucleationModel_LL : public NucleationModel
{
public:
	NucleationModel_LL() : NucleationModel(NucleationMechanism::LL) {}

	[[nodiscard]] double getNucleationRate(MomentState& state, const std::vector<double>& particleSizes, const std::vector<double>& particleWeights, MassRateRatio& ratio) const override;

	~NucleationModel_LL() override = default;
};
}

#endif //NUCLEATIONMODEL_LL_H
