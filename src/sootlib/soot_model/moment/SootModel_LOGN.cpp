#include "SootModel_LOGN.h"
soot::SootModel_LOGN* soot::SootModel_LOGN::getInstance(std::unique_ptr<CoagulationModel> coagulationModel,
                                                        std::unique_ptr<GrowthModel> growthModel,
                                                        std::unique_ptr<NucleationModel> nucleationModel,
                                                        std::unique_ptr<OxidationModel> oxidationModel)
{
	return new SootModel_LOGN(std::move(coagulationModel),
						   std::move(growthModel),
						   std::move(nucleationModel),
						   std::move(oxidationModel));
}
soot::SootModel_LOGN::SootModel_LOGN(std::unique_ptr<CoagulationModel> coagulationModel,
                                     std::unique_ptr<GrowthModel> growthModel,
                                     std::unique_ptr<NucleationModel> nucleationModel,
                                     std::unique_ptr<OxidationModel> oxidationModel) : MomentSootModel(std::move(coagulationModel),
                                                                                                    std::move(growthModel),
                                                                                                    std::move(nucleationModel),
                                                                                                    std::move(oxidationModel))
{
}
soot::SourceTerms soot::SootModel_LOGN::getSourceTerms(soot::MomentState& state) const
{
	// TODO implement
	return SourceTerms();
}
