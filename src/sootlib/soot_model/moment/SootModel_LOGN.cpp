#include "SootModel_LOGN.h"
soot::SootModel_LOGN* soot::SootModel_LOGN::getInstance(std::unique_ptr<CoagulationModel> coagulationModel,
                                                        std::unique_ptr<GrowthModel> growthModel,
                                                        std::unique_ptr<NucleationModel> nucleationModel,
                                                        std::unique_ptr<OxidationModel> oxidationModel,
                                                        soot::CoagulationMechanism coagulationMechanism,
                                                        soot::GrowthMechanism growthMechanism,
                                                        soot::NucleationMechanism nucleationMechanism,
                                                        soot::OxidationMechanism oxidationMechanism)
{
	return new SootModel_LOGN(std::move(coagulationModel),
						   std::move(growthModel),
						   std::move(nucleationModel),
						   std::move(oxidationModel),
						   coagulationMechanism,
						   growthMechanism,
						   nucleationMechanism,
						   oxidationMechanism);
}
soot::SootModel_LOGN::SootModel_LOGN(std::unique_ptr<CoagulationModel> coagulationModel,
                                     std::unique_ptr<GrowthModel> growthModel,
                                     std::unique_ptr<NucleationModel> nucleationModel,
                                     std::unique_ptr<OxidationModel> oxidationModel,
                                     soot::CoagulationMechanism coagulationMechanism,
                                     soot::GrowthMechanism growthMechanism,
                                     soot::NucleationMechanism nucleationMechanism,
                                     soot::OxidationMechanism oxidationMechanism) : MomentSootModel(std::move(coagulationModel),
                                                                                                    std::move(growthModel),
                                                                                                    std::move(nucleationModel),
                                                                                                    std::move(oxidationModel),
                                                                                                    coagulationMechanism,
                                                                                                    growthMechanism,
                                                                                                    nucleationMechanism,
                                                                                                    oxidationMechanism)
{
}
soot::SourceTerms soot::SootModel_LOGN::getSourceTerms(soot::MomentState& state) const
{
	// TODO implement
	return SourceTerms();
}
