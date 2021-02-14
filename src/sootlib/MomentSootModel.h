#ifndef MOMENTSOOTMODEL_H
#define MOMENTSOOTMODEL_H

#include "sootlib/SourceTerms.h"
#include "sootlib/state/gas/GasState.h"
#include "sootlib/state/soot/MomentSootState.h"
#include "sootlib/soot_models/SootModel_Base.h"

namespace soot
{
class MomentSootModel : public SootModel_Base
{
public:
	MomentSootModel(std::unique_ptr<CoagulationModel> coagulationModel,
	                std::unique_ptr<GrowthModel> growthModel,
	                std::unique_ptr<NucleationModel> nucleationModel,
	                std::unique_ptr<OxidationModel> oxidationModel) : SootModel_Base(std::move(coagulationModel), std::move(growthModel), std::move(nucleationModel), std::move(oxidationModel))
	{}

	[[nodiscard]] virtual SourceTerms getSourceTerms(const GasState& gasState, const MomentSootState& sootState) const = 0;

	virtual ~MomentSootModel() = default;
};
}

#endif //MOMENTSOOTMODEL_H
