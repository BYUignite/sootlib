#ifndef SOOTMODEL_BASE_H
#define SOOTMODEL_BASE_H

#include "sootlib/SootModel.h"
#include "sootlib/coagulation_model/CoagulationModel.h"
#include "sootlib/growth_model/GrowthModel.h"
#include "sootlib/nucleation_model/NucleationModel.h"
#include "sootlib/oxidation_model/OxidationModel.h"

namespace soot
{
class SootModel_Base : public SootModel
{
protected:
	/* Calculation Models */

	CoagulationModel coagulationModel;
	GrowthModel growthModel;
	NucleationModel nucleationModel;
	OxidationModel oxidationModel;

private:

};
}

#endif //SOOTMODEL_BASE_H
