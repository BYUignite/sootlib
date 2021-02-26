#ifndef NUCLEATIONMODEL_LL_H
#define NUCLEATIONMODEL_LL_H

#include "sootlib/state/gas/GasState.h"
#include "sootlib/state/soot/MomentSootState.h"
#include "sootlib/nucleation_model/NucleationModel.h"

namespace soot
{
class NucleationModel_LL : public NucleationModel
{
public:
	[[nodiscard]] double getNucleationRate(const GasState& gasState, const MomentSootState& sootState, const std::vector<double>& particleSizes, const std::vector<double>& particleWeights) const override;

	~NucleationModel_LL() override = default;
};
}

#endif //NUCLEATIONMODEL_LL_H
