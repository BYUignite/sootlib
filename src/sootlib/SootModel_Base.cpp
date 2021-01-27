#include "SootModel_Base.h"
soot::SootModel_Base::SootModel_Base(std::unique_ptr<CoagulationModel> coagulationModel,
                                     std::unique_ptr<GrowthModel> growthModel,
                                     std::unique_ptr<NucleationModel> nucleationModel,
                                     std::unique_ptr<OxidationModel> oxidationModel)
{
	this->coagulationModel = std::move(coagulationModel);
	this->growthModel = std::move(growthModel);
	this->nucleationModel = std::move(nucleationModel);
	this->oxidationModel = std::move(oxidationModel);
}
