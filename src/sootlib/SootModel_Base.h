#ifndef SOOTMODEL_BASE_H
#define SOOTMODEL_BASE_H

#include <memory>

#include "sootlib/SootModel.h"
#include "sootlib/coagulation_model/CoagulationModel.h"
#include "sootlib/coagulation_model/CoagulationModel_NONE.h"
#include "sootlib/growth_model/GrowthModel.h"
#include "sootlib/growth_model/GrowthModel_NONE.h"
#include "sootlib/nucleation_model/NucleationModel.h"
#include "sootlib/nucleation_model/NucleationModel_NONE.h"
#include "sootlib/oxidation_model/OxidationModel.h"
#include "sootlib/oxidation_model/OxidationModel_NONE.h"

namespace soot
{
class SootModel_Base : public SootModel
{
protected:
	/* Calculation Models */

	std::unique_ptr<CoagulationModel> coagulationModel;
	std::unique_ptr<GrowthModel> growthModel;
	std::unique_ptr<NucleationModel> nucleationModel;
	std::unique_ptr<OxidationModel> oxidationModel;

	SootModel_Base(std::unique_ptr<CoagulationModel> coagulationModel,
				std::unique_ptr<GrowthModel> growthModel,
				std::unique_ptr<NucleationModel> nucleationModel,
				std::unique_ptr<OxidationModel> oxidationModel);
};
}

#endif //SOOTMODEL_BASE_H
