#include "SootModel_SECT.h"

using namespace std;
using namespace soot;

SootModel_SECT* SootModel_SECT::getInstance(unique_ptr<CoagulationModel> coagulationModel,
                                                        unique_ptr<GrowthModel> growthModel,
                                                        unique_ptr<NucleationModel> nucleationModel,
                                                        unique_ptr<OxidationModel> oxidationModel)
{
	return new SootModel_SECT(move(coagulationModel),
	                          move(growthModel),
	                          move(nucleationModel),
	                          move(oxidationModel));
}
SootModel_SECT::SootModel_SECT(unique_ptr<CoagulationModel> coagulationModel,
                                     unique_ptr<GrowthModel> growthModel,
                                     unique_ptr<NucleationModel> nucleationModel,
                                     unique_ptr<OxidationModel> oxidationModel) : SootModel_Base(move(coagulationModel),
                                                                                                    move(growthModel),
                                                                                                    move(nucleationModel),
                                                                                                    move(oxidationModel))
{}
SourceTerms SootModel_SECT::getSourceTerms(const soot::BinState& state) const
{
	// TODO implement

	return SourceTerms();
}
