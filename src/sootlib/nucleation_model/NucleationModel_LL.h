#ifndef NUCLEATIONMODEL_LL_H
#define NUCLEATIONMODEL_LL_H

#include "sootlib/state/GasState.h"
#include "sootlib/state/MomentSootState.h"
#include "sootlib/nucleation_model/NucleationModel.h"

namespace soot
{
class NucleationModel_LL : public NucleationModel
{
public:
	// TODO implement
	[[nodiscard]] double getNucleationRate(const GasState& gasState, const MomentSootState& sootState) const override;

	~NucleationModel_LL() override = default;
};
}

#endif //NUCLEATIONMODEL_LL_H
