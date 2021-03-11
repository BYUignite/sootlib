#ifndef SOOTMODEL_BASE_H
#define SOOTMODEL_BASE_H

#include <memory>

#include "sootlib/coagulation_model/CoagulationModel.h"
#include "sootlib/growth_model/GrowthModel.h"
#include "sootlib/nucleation_model/NucleationModel.h"
#include "sootlib/oxidation_model/OxidationModel.h"
#include "sootlib/MassRateRatio.h"

namespace soot
{
class SootModel_Base
{
protected:
	/* Calculation Models */

	const std::unique_ptr<CoagulationModel> coagulationModel;
	const std::unique_ptr<GrowthModel> growthModel;
	const std::unique_ptr<NucleationModel> nucleationModel;
	const std::unique_ptr<OxidationModel> oxidationModel;

	const CoagulationMechanism coagulationMechanism;
	const GrowthMechanism growthMechanism;
	const NucleationMechanism nucleationMechanism;
	const OxidationMechanism oxidationMechanism;

	SootModel_Base(std::unique_ptr<CoagulationModel> coagulationModel,
	               std::unique_ptr<GrowthModel> growthModel,
	               std::unique_ptr<NucleationModel> nucleationModel,
	               std::unique_ptr<OxidationModel> oxidationModel,
	               CoagulationMechanism coagulationMechanism,
	               GrowthMechanism growthMechanism,
	               NucleationMechanism nucleationMechanism,
	               OxidationMechanism oxidationMechanism);

	static void initializeGasSpecies(std::map<GasSpecies, double>& gasSourceTerms, std::map<size_t, double>& PAHSourceTerms, const MassRateRatio& ratio);
};
}

#endif //SOOTMODEL_BASE_H
