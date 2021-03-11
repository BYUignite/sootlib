#ifndef BINSOOTMODEL_H
#define BINSOOTMODEL_H

#include "sootlib/SourceTerms.h"
#include "sootlib/state/BinState.h"
#include "sootlib/soot_model/SootModel_Base.h"

namespace soot
{
class BinSootModel : public SootModel_Base
{
public:
	BinSootModel(std::unique_ptr<CoagulationModel> coagulationModel,
	             std::unique_ptr<GrowthModel> growthModel,
	             std::unique_ptr<NucleationModel> nucleationModel,
	             std::unique_ptr<OxidationModel> oxidationModel,
	             CoagulationMechanism coagulationMechanism,
	             GrowthMechanism growthMechanism,
	             NucleationMechanism nucleationMechanism,
	             OxidationMechanism oxidationMechanism) : SootModel_Base(std::move(coagulationModel),
																	  std::move(growthModel),
																	  std::move(nucleationModel),
																	  std::move(oxidationModel),
																	  coagulationMechanism,
																	  growthMechanism,
																	  nucleationMechanism,
																	  oxidationMechanism)
	{}

	[[nodiscard]] virtual SourceTerms getSourceTerms(const BinState& state) const = 0;

	virtual ~BinSootModel() = default;
};
}

#endif //BINSOOTMODEL_H
