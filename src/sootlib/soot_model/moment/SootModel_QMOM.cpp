#include "SootModel_QMOM.h"
soot::SootModel_QMOM* soot::SootModel_QMOM::getInstance(std::unique_ptr<CoagulationModel> coagulationModel,
                                                        std::unique_ptr<GrowthModel> growthModel,
                                                        std::unique_ptr<NucleationModel> nucleationModel,
                                                        std::unique_ptr<OxidationModel> oxidationModel)
{
	return new SootModel_QMOM(std::move(coagulationModel),
	                          std::move(growthModel),
	                          std::move(nucleationModel),
	                          std::move(oxidationModel));
}
soot::SootModel_QMOM::SootModel_QMOM(std::unique_ptr<CoagulationModel> coagulationModel,
                                     std::unique_ptr<GrowthModel> growthModel,
                                     std::unique_ptr<NucleationModel> nucleationModel,
                                     std::unique_ptr<OxidationModel> oxidationModel) : MomentSootModel(std::move(coagulationModel),
                                                                                                    std::move(growthModel),
                                                                                                    std::move(nucleationModel),
                                                                                                    std::move(oxidationModel))
{
}
soot::SourceTerms soot::SootModel_QMOM::getSourceTerms(soot::MomentState& state) const
{
	// TODO implement
	return SourceTerms();
}
