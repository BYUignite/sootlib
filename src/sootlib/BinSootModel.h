#ifndef BINSOOTMODEL_H
#define BINSOOTMODEL_H

#include "sootlib/SootSourceTerms.h"
#include "sootlib/state/gas/GasState.h"
#include "sootlib/state/soot/BinSootState.h"
#include "sootlib/soot_models/SootModel_Base.h"

namespace soot
{
class BinSootModel : public SootModel_Base
{
public:
	BinSootModel(std::unique_ptr<CoagulationModel> coagulationModel,
	             std::unique_ptr<GrowthModel> growthModel,
	             std::unique_ptr<NucleationModel> nucleationModel,
	             std::unique_ptr<OxidationModel> oxidationModel) : SootModel_Base(std::move(coagulationModel), std::move(growthModel), std::move(nucleationModel), std::move(oxidationModel))
	{}

	[[nodiscard]] virtual SootSourceTerms getSourceTerms(const GasState& gasState, const BinSootState& sootState) const = 0;

	virtual ~BinSootModel() = default;
};
}

#endif //BINSOOTMODEL_H
