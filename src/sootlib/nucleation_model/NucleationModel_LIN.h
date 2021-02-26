#ifndef NUCLEATIONMODEL_LIN_H
#define NUCLEATIONMODEL_LIN_H

#include "sootlib/state/gas/State.h"
#include "sootlib/state/soot/MomentSootState.h"
#include "sootlib/nucleation_model/NucleationModel.h"

namespace soot
{
class NucleationModel_LIN : public NucleationModel
{
public:
	[[nodiscard]] double getNucleationRate(const State& gasState, const MomentSootState& sootState, const std::vector<double>& particleSizes, const std::vector<double>& particleWeights) const override;

	~NucleationModel_LIN() override = default;
};
}

#endif //NUCLEATIONMODEL_LIN_H
