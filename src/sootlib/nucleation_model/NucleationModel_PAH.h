#ifndef NUCLEATIONMODEL_PAH_H
#define NUCLEATIONMODEL_PAH_H

#include "sootlib/state/GasState.h"
#include "sootlib/state/SootState.h"
#include "sootlib/nucleation_model/NucleationModel.h"

namespace soot
{
class NucleationModel_PAH : public NucleationModel
{
public:
	// TODO implement
	[[nodiscard]] double getNucleationRate(const GasState& gasState, const SootState& sootState) const override;

	~NucleationModel_PAH() override = default;
};
}

#endif //NUCLEATIONMODEL_PAH_H
