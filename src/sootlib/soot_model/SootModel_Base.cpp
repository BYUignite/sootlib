#include "SootModel_Base.h"
soot::SootModel_Base::SootModel_Base(std::unique_ptr<CoagulationModel> coagulationModel,
                                     std::unique_ptr<GrowthModel> growthModel,
                                     std::unique_ptr<NucleationModel> nucleationModel,
                                     std::unique_ptr<OxidationModel> oxidationModel,
                                     CoagulationMechanism coagulationMechanism,
                                     GrowthMechanism growthMechanism,
                                     NucleationMechanism nucleationMechanism,
                                     OxidationMechanism oxidationMechanism)
	: coagulationModel(std::move(coagulationModel)),
	  growthModel(std::move(growthModel)),
	  nucleationModel(std::move(nucleationModel)),
	  oxidationModel(std::move(oxidationModel)),
	  coagulationMechanism(coagulationMechanism),
	  growthMechanism(growthMechanism),
	  nucleationMechanism(nucleationMechanism),
	  oxidationMechanism(oxidationMechanism)
{
}
