#include "SootModel_MOMIC.h"

using namespace std;
using namespace soot;

SootModel_MOMIC* SootModel_MOMIC::getInstance(unique_ptr<CoagulationModel> coagulationModel,
                                                          unique_ptr<GrowthModel> growthModel,
                                                          unique_ptr<NucleationModel> nucleationModel,
                                                          unique_ptr<OxidationModel> oxidationModel)
{
	return new SootModel_MOMIC(move(coagulationModel),
	                           move(growthModel),
	                           move(nucleationModel),
	                           move(oxidationModel));
}
SootModel_MOMIC::SootModel_MOMIC(unique_ptr<CoagulationModel> coagulationModel,
                                       unique_ptr<GrowthModel> growthModel,
                                       unique_ptr<NucleationModel> nucleationModel,
                                       unique_ptr<OxidationModel> oxidationModel) : SootModel_Base(move(coagulationModel),
                                                                                                      move(growthModel),
                                                                                                      move(nucleationModel),
                                                                                                      move(oxidationModel))
{
}
SourceTerms SootModel_MOMIC::getSourceTerms(MomentState& state) const
{
	// TODO implement
	return SourceTerms();
}
