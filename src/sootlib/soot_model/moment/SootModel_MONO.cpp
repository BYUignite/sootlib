#include "SootModel_MONO.h"
soot::SootModel_MONO::SootModel_MONO(std::unique_ptr<CoagulationModel> coagulationModel,
                                     std::unique_ptr<GrowthModel> growthModel,
                                     std::unique_ptr<NucleationModel> nucleationModel,
                                     std::unique_ptr<OxidationModel> oxidationModel)
	: MomentSootModel(std::move(coagulationModel),
	                 std::move(growthModel),
	                 std::move(nucleationModel),
	                 std::move(oxidationModel))
{
}
soot::SootModel_MONO* soot::SootModel_MONO::getInstance(std::unique_ptr<CoagulationModel> coagulationModel,
                                                        std::unique_ptr<GrowthModel> growthModel,
                                                        std::unique_ptr<NucleationModel> nucleationModel,
                                                        std::unique_ptr<OxidationModel> oxidationModel)
{
	return new SootModel_MONO(std::move(coagulationModel),
	                          std::move(growthModel),
	                          std::move(nucleationModel),
	                          std::move(oxidationModel));
}
soot::SourceTerms soot::SootModel_MONO::getSourceTerms(const MomentState& state) const
{
	return SourceTerms();
}
