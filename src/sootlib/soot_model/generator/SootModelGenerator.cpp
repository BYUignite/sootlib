#include "SootModelGenerator.h"

using namespace std;
using namespace soot;

SootModelGenerator::SootModelGenerator()
{
	nucleationMechanism = NucleationMechanism::NONE;
	growthMechanism = GrowthMechanism::NONE;
	oxidationMechanism = OxidationMechanism::NONE;
	coagulationMechanism = CoagulationMechanism::NONE;
}
void SootModelGenerator::setNucleationMechanism(NucleationMechanism mechanism)
{
	nucleationMechanism = mechanism;
}
void SootModelGenerator::setGrowthMechanism(GrowthMechanism mechanism)
{
	growthMechanism = mechanism;
}
void SootModelGenerator::setOxidationMechanism(OxidationMechanism mechanism)
{
	oxidationMechanism = mechanism;
}
void SootModelGenerator::setCoagulationMechanism(CoagulationMechanism mechanism)
{
	coagulationMechanism = mechanism;
}
unique_ptr<CoagulationModel> SootModelGenerator::getCoagulationModel() const
{
	switch (coagulationMechanism)
	{
		case CoagulationMechanism::NONE:
			return make_unique<CoagulationModel_NONE>();
		case CoagulationMechanism::LL:
			return make_unique<CoagulationModel_LL>();
		case CoagulationMechanism::FUCHS:
			make_unique<CoagulationModel_FUCHS>();
		case CoagulationMechanism::FRENK:
			make_unique<CoagulationModel_FRENK>();
		default:
			throw domain_error("Bad soot coagulation mechanism");
	}
}
unique_ptr<GrowthModel> SootModelGenerator::getGrowthModel() const
{
	switch (growthMechanism)
	{
		case GrowthMechanism::NONE:
			return make_unique<GrowthModel_NONE>();
		case GrowthMechanism::LL:
			return make_unique<GrowthModel_LL>();
		case GrowthMechanism::LIN:
			return make_unique<GrowthModel_LIN>();
		case GrowthMechanism::HACA:
			return make_unique<GrowthModel_HACA>();
		default:
			throw domain_error("Bad soot growth mechanism");
	}
}
unique_ptr<NucleationModel> SootModelGenerator::getNucleationModel() const
{
	switch (nucleationMechanism)
	{
		case NucleationMechanism::NONE:
			return make_unique<NucleationModel_NONE>();
		case NucleationMechanism::LL:
			return make_unique<NucleationModel_LL>();
		case NucleationMechanism::LIN:
			return make_unique<NucleationModel_LIN>();
		case NucleationMechanism::PAH:
			return make_unique<NucleationModel_PAH>();
		default:
			throw domain_error("Bad soot nucleation mechanism");
	}
}
unique_ptr<OxidationModel> SootModelGenerator::getOxidationModel() const
{
	switch (oxidationMechanism)
	{
		case OxidationMechanism::NONE:
			return make_unique<OxidationModel_NONE>();
		case OxidationMechanism::LL:
			return make_unique<OxidationModel_LL>();
		case OxidationMechanism::LEE_NEOH:
			return make_unique<OxidationModel_LEE_NEOH>();
		case OxidationMechanism::NSC_NEOH:
			return make_unique<OxidationModel_NSC_NEOH>();
		case OxidationMechanism::HACA:
			return make_unique<OxidationModel_HACA>();
		default:
			throw domain_error("Bad soot oxidation model");
	}
}
