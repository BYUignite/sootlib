#include "SootModel_Base.h"
soot::SootModel_Base::SootModel_Base(std::unique_ptr<CoagulationModel> coagulationModel,
                                     std::unique_ptr<GrowthModel> growthModel,
                                     std::unique_ptr<NucleationModel> nucleationModel,
                                     std::unique_ptr<OxidationModel> oxidationModel)
	: coagulationModel(std::move(coagulationModel)),
	  growthModel(std::move(growthModel)),
	  nucleationModel(std::move(nucleationModel)),
	  oxidationModel(std::move(oxidationModel))
{
}
void soot::SootModel_Base::initializeGasSpecies(std::map<GasSpecies, double>& gasSourceTerms,
                                                std::map<size_t, double>& PAHSourceTerms,
                                                const soot::MassRateRatio& ratio)
{
	for (auto it = ratio.gasSpeciesBegin(); it != ratio.gasSpeciesEnd(); it++)
		gasSourceTerms[it->first] = 0;
	for (auto it = ratio.PAHBegin(); it != ratio.PAHEnd(); it++)
		PAHSourceTerms[it->first] = 0;
}
