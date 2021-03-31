#include "SootModel_LOGN.h"

using namespace soot;

SootModel_LOGN* SootModel_LOGN::getInstance(std::unique_ptr<CoagulationModel> coagulationModel,
                                                        std::unique_ptr<GrowthModel> growthModel,
                                                        std::unique_ptr<NucleationModel> nucleationModel,
                                                        std::unique_ptr<OxidationModel> oxidationModel)
{
	return new SootModel_LOGN(std::move(coagulationModel),
						   std::move(growthModel),
						   std::move(nucleationModel),
						   std::move(oxidationModel));
}
SootModel_LOGN::SootModel_LOGN(std::unique_ptr<CoagulationModel> coagulationModel,
                                     std::unique_ptr<GrowthModel> growthModel,
                                     std::unique_ptr<NucleationModel> nucleationModel,
                                     std::unique_ptr<OxidationModel> oxidationModel) : SootModel_Base(std::move(coagulationModel),
                                                                                                    std::move(growthModel),
                                                                                                    std::move(nucleationModel),
                                                                                                    std::move(oxidationModel))
{
}
SourceTerms SootModel_LOGN::getSourceTerms(MomentState& state) const
{
	// TODO implement
	return SourceTerms();
}
