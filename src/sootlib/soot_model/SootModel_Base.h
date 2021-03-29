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

	SootModel_Base(std::unique_ptr<CoagulationModel> coagulationModel,
	               std::unique_ptr<GrowthModel> growthModel,
	               std::unique_ptr<NucleationModel> nucleationModel,
	               std::unique_ptr<OxidationModel> oxidationModel);
};
}

#endif //SOOTMODEL_BASE_H
