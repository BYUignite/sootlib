#include "SootModel_MOMIC.h"

using namespace soot;

SootModel_MOMIC* SootModel_MOMIC::getInstance(std::unique_ptr<CoagulationModel> coagulationModel,
                                                          std::unique_ptr<GrowthModel> growthModel,
                                                          std::unique_ptr<NucleationModel> nucleationModel,
                                                          std::unique_ptr<OxidationModel> oxidationModel)
{
	return new SootModel_MOMIC(std::move(coagulationModel),
	                           std::move(growthModel),
	                           std::move(nucleationModel),
	                           std::move(oxidationModel));
}
SootModel_MOMIC::SootModel_MOMIC(std::unique_ptr<CoagulationModel> coagulationModel,
                                       std::unique_ptr<GrowthModel> growthModel,
                                       std::unique_ptr<NucleationModel> nucleationModel,
                                       std::unique_ptr<OxidationModel> oxidationModel) : SootModel_Base(std::move(coagulationModel),
                                                                                                      std::move(growthModel),
                                                                                                      std::move(nucleationModel),
                                                                                                      std::move(oxidationModel))
{
}
SourceTerms SootModel_MOMIC::getSourceTerms(MomentState& state) const
{
	// TODO implement
	return SourceTerms();
}
