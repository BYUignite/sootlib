#include "SootModel_SECT.h"
soot::SootModel_SECT* soot::SootModel_SECT::getInstance(std::unique_ptr<CoagulationModel> coagulationModel,
                                                        std::unique_ptr<GrowthModel> growthModel,
                                                        std::unique_ptr<NucleationModel> nucleationModel,
                                                        std::unique_ptr<OxidationModel> oxidationModel,
                                                        CoagulationMechanism coagulationMechanism,
                                                        GrowthMechanism growthMechanism,
                                                        NucleationMechanism nucleationMechanism,
                                                        OxidationMechanism oxidationMechanism)
{
	return new SootModel_SECT(std::move(coagulationModel),
	                          std::move(growthModel),
	                          std::move(nucleationModel),
	                          std::move(oxidationModel),
	                          coagulationMechanism,
	                          growthMechanism,
	                          nucleationMechanism,
	                          oxidationMechanism);
}
soot::SootModel_SECT::SootModel_SECT(std::unique_ptr<CoagulationModel> coagulationModel,
                                     std::unique_ptr<GrowthModel> growthModel,
                                     std::unique_ptr<NucleationModel> nucleationModel,
                                     std::unique_ptr<OxidationModel> oxidationModel,
                                     CoagulationMechanism coagulationMechanism,
                                     GrowthMechanism growthMechanism,
                                     NucleationMechanism nucleationMechanism,
                                     OxidationMechanism oxidationMechanism) : BinSootModel(std::move(coagulationModel),
                                                                                                    std::move(growthModel),
                                                                                                    std::move(nucleationModel),
                                                                                                    std::move(oxidationModel),
                                                                                                    coagulationMechanism,
                                                                                                    growthMechanism,
                                                                                                    nucleationMechanism,
                                                                                                    oxidationMechanism)
{}
soot::SourceTerms soot::SootModel_SECT::getSourceTerms(const soot::BinState& state) const
{
	// TODO implement

	return SourceTerms();
}
