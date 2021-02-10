#include "SootModelFactory.h"
soot::SootModelFactory::SootModelFactory()
{
	nucleationMechanism = NucleationMechanism::NONE;
	growthMechanism = GrowthMechanism::NONE;
	oxidationMechanism = OxidationMechanism::NONE;
	coagulationMechanism = CoagulationMechanism::NONE;
}
void soot::SootModelFactory::setNucleationMechanism(soot::NucleationMechanism mechanism)
{
	nucleationMechanism = mechanism;
}
void soot::SootModelFactory::setGrowthMechanism(soot::GrowthMechanism mechanism)
{
	growthMechanism = mechanism;
}
void soot::SootModelFactory::setOxidationMechanism(soot::OxidationMechanism mechanism)
{
	oxidationMechanism = mechanism;
}
void soot::SootModelFactory::setCoagulationMechanism(soot::CoagulationMechanism mechanism)
{
	coagulationMechanism = mechanism;
}
std::unique_ptr<soot::CoagulationModel> soot::SootModelFactory::getCoagulationModel() const
{
	switch (coagulationMechanism)
	{
		case CoagulationMechanism::NONE:
			return std::make_unique<CoagulationModel_NONE>();
		case CoagulationMechanism::LL:
			return std::make_unique<CoagulationModel_LL>();
		case CoagulationMechanism::FUCHS:
			std::make_unique<CoagulationModel_FUCHS>();
		case CoagulationMechanism::FRENK:
			std::make_unique<CoagulationModel_FRENK>();
		default:
			throw std::domain_error("Bad soot coagulation mechanism");
	}
}
std::unique_ptr<soot::GrowthModel> soot::SootModelFactory::getGrowthModel() const
{
	switch (growthMechanism)
	{
		case GrowthMechanism::NONE:
			return std::make_unique<GrowthModel_NONE>();
		case GrowthMechanism::LL:
			return std::make_unique<GrowthModel_LL>();
		case GrowthMechanism::LIN:
			return std::make_unique<GrowthModel_LIN>();
		case GrowthMechanism::HACA:
			return std::make_unique<GrowthModel_HACA>();
		default:
			throw std::domain_error("Bad soot growth mechanism");
	}
}
std::unique_ptr<soot::NucleationModel> soot::SootModelFactory::getNucleationModel() const
{
	switch (nucleationMechanism)
	{
		case NucleationMechanism::NONE:
			return std::make_unique<NucleationModel_NONE>();
		case NucleationMechanism::LL:
			return std::make_unique<NucleationModel_LL>();
		case NucleationMechanism::LIN:
			return std::make_unique<NucleationModel_LIN>();
		case NucleationMechanism::PAH:
			return std::make_unique<NucleationModel_PAH>();
		default:
			throw std::domain_error("Bad soot nucleation mechanism");
	}
}
std::unique_ptr<soot::OxidationModel> soot::SootModelFactory::getOxidationModel() const
{
	switch (oxidationMechanism)
	{
		case OxidationMechanism::NONE:
			return std::make_unique<OxidationModel_NONE>();
		case OxidationMechanism::LL:
			return std::make_unique<OxidationModel_LL>();
		case OxidationMechanism::LEE_NEOH:
			return std::make_unique<OxidationModel_LEE_NEOH>();
		case OxidationMechanism::NSC_NEOH:
			return std::make_unique<OxidationModel_NSC_NEOH>();
		case OxidationMechanism::HACA:
			return std::make_unique<OxidationModel_HACA>();
		default:
			throw std::domain_error("Bad soot oxidation model");
	}
}
