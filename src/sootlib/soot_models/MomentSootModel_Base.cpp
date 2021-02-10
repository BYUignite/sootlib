#include "MomentSootModel_Base.h"
soot::MomentSootModel_Base::MomentSootModel_Base(std::unique_ptr<CoagulationModel> coagulationModel,
                                                 std::unique_ptr<GrowthModel> growthModel,
                                                 std::unique_ptr<NucleationModel> nucleationModel,
                                                 std::unique_ptr<OxidationModel> oxidationModel,
                                                 size_t numSootVars)
	: numSootVars(numSootVars),
	  coagulationModel(std::move(coagulationModel)),
	  growthModel(std::move(growthModel)),
	  nucleationModel(std::move(nucleationModel)),
	  oxidationModel(std::move(oxidationModel))
{
}
