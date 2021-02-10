#ifndef MOMENTSOOTMODEL_BASE_H
#define MOMENTSOOTMODEL_BASE_H

#include <memory>

#include "sootlib/MomentSootModel.h"
#include "sootlib/coagulation_model/CoagulationModel.h"
#include "sootlib/growth_model/GrowthModel.h"
#include "sootlib/nucleation_model/NucleationModel.h"
#include "sootlib/oxidation_model/OxidationModel.h"

namespace soot
{
class MomentSootModel_Base : public MomentSootModel
{
protected:
	/* Calculation Models */

	const std::unique_ptr<CoagulationModel> coagulationModel;
	const std::unique_ptr<GrowthModel> growthModel;
	const std::unique_ptr<NucleationModel> nucleationModel;
	const std::unique_ptr<OxidationModel> oxidationModel;

	MomentSootModel_Base(std::unique_ptr<CoagulationModel> coagulationModel,
	                     std::unique_ptr<GrowthModel> growthModel,
	                     std::unique_ptr<NucleationModel> nucleationModel,
	                     std::unique_ptr<OxidationModel> oxidationModel,
	                     size_t numSootVars);

	// TODO should all of these be const
	// another question might be if every member of this class should be const
	/* variables */
	const size_t numSootVars;
};
}

#endif //MOMENTSOOTMODEL_BASE_H
