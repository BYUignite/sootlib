#ifndef NUCLEATIONMODEL_NONE_H
#define NUCLEATIONMODEL_NONE_H

#include "sootlib/state/GasState.h"
#include "sootlib/state/SootState.h"
#include "sootlib/nucleation_model/NucleationModel.h"

namespace soot
{
class NucleationModel_NONE : public NucleationModel
{
public:
	[[nodiscard]] double getNucleationRate(const GasState& gasState, const SootState& sootState) const override
	{
		return 0.0;
	}

	~NucleationModel_NONE() override = default;
};
}

#endif //NUCLEATIONMODEL_NONE_H
