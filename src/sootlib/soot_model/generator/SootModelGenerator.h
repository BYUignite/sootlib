#ifndef BASESOOTMODELFACTORY_H
#define BASESOOTMODELFACTORY_H

/* static variables */
#include "sootlib/static.h"

/* soot models */
#include "sootlib/soot_models/moment/SootModel_LOGN.h"
#include "sootlib/soot_models/moment/SootModel_MOMIC.h"
#include "sootlib/soot_models/moment/SootModel_MONO.h"
#include "sootlib/soot_models/moment/SootModel_QMOM.h"

/* coagulation models */
#include "sootlib/coagulation_model/CoagulationModel.h"
#include "sootlib/coagulation_model/CoagulationModel_FRENK.h"
#include "sootlib/coagulation_model/CoagulationModel_FUCHS.h"
#include "sootlib/coagulation_model/CoagulationModel_LL.h"
#include "sootlib/coagulation_model/CoagulationModel_NONE.h"

/* growth models */
#include "sootlib/growth_model/GrowthModel.h"
#include "sootlib/growth_model/GrowthModel_HACA.h"
#include "sootlib/growth_model/GrowthModel_LIN.h"
#include "sootlib/growth_model/GrowthModel_LL.h"
#include "sootlib/growth_model/GrowthModel_NONE.h"

/* nucleation models */
#include "sootlib/nucleation_model/NucleationModel.h"
#include "sootlib/nucleation_model/NucleationModel_LIN.h"
#include "sootlib/nucleation_model/NucleationModel_LL.h"
#include "sootlib/nucleation_model/NucleationModel_NONE.h"
#include "sootlib/nucleation_model/NucleationModel_PAH.h"

/* oxidation models */
#include "sootlib/oxidation_model/OxidationModel.h"
#include "sootlib/oxidation_model/OxidationModel_HACA.h"
#include "sootlib/oxidation_model/OxidationModel_LEE_NEOH.h"
#include "sootlib/oxidation_model/OxidationModel_LL.h"
#include "sootlib/oxidation_model/OxidationModel_NONE.h"
#include "sootlib/oxidation_model/OxidationModel_NSC_NEOH.h"

namespace soot
{
class SootModelGenerator
{
public:
	void setNucleationMechanism(NucleationMechanism mechanism);
	void setGrowthMechanism(GrowthMechanism mechanism);
	void setOxidationMechanism(OxidationMechanism mechanism);
	void setCoagulationMechanism(CoagulationMechanism mechanism);

protected:
	SootModelGenerator();

	NucleationMechanism nucleationMechanism;
	GrowthMechanism growthMechanism;
	OxidationMechanism oxidationMechanism;
	CoagulationMechanism coagulationMechanism;

	[[nodiscard]] std::unique_ptr<CoagulationModel> getCoagulationModel() const;
	[[nodiscard]] std::unique_ptr<GrowthModel> getGrowthModel() const;
	[[nodiscard]] std::unique_ptr<NucleationModel> getNucleationModel() const;
	[[nodiscard]] std::unique_ptr<OxidationModel> getOxidationModel() const;
};
}

#endif //BASESOOTMODELFACTORY_H
