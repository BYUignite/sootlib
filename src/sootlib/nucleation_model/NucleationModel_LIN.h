#ifndef NUCLEATIONMODEL_LIN_H
#define NUCLEATIONMODEL_LIN_H

#include "sootlib/state/GasState.h"
#include "sootlib/state/SootState.h"
#include "sootlib/nucleation_model/NucleationModel.h"

namespace soot
{
class NucleationModel_LIN : public NucleationModel
{
public:
	// TODO implement
	[[nodiscard]] double getNucleationRate(const GasState& gasState, const SootState& sootState) const override;

	~NucleationModel_LIN() override = default;
};
}

#endif //NUCLEATIONMODEL_LIN_H
