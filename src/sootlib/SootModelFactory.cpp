#include "SootModelFactory.h"
void soot::SootModelFactory::setModel(soot::Model model)
{
	this->model = model;
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
soot::SootModel* soot::SootModelFactory::getModel() const
{
	/* create helper models */
	std::unique_ptr<CoagulationModel> cm;
	std::unique_ptr<GrowthModel> gm;
	std::unique_ptr<NucleationModel> nm;
	std::unique_ptr<OxidationModel> om;

	switch (coagulationMechanism)
	{
		case CoagulationMechanism::NONE:
			cm = std::make_unique<CoagulationModel_NONE>();
			break;
		case CoagulationMechanism::LL:
			// TODO
			break;
		case CoagulationMechanism::FUCHS:
			// TODO
			break;
		case CoagulationMechanism::FRENK:
			// TODO
			break;
		default:
			throw std::domain_error("Bad soot coagulation mechanism");
	}

	switch (growthMechanism)
	{
		case GrowthMechanism::NONE:
			gm = std::make_unique<GrowthModel_NONE>();
			break;
		case GrowthMechanism::LL:
			// TODO
			break;
		case GrowthMechanism::LIN:
			// TODO
			break;
		case GrowthMechanism::HACA:
			// TODO
			break;
		default:
			throw std::domain_error("Bad soot growth mechanism");
	}

	switch (nucleationMechanism)
	{
		case NucleationMechanism::NONE:
			nm = std::make_unique<NucleationModel_NONE>();
			break;
		case NucleationMechanism::LL:
			// TODO
			break;
		case NucleationMechanism::LIN:
			// TODO
			break;
		case NucleationMechanism::PAH:
			// TODO
			break;
		default:
			throw std::domain_error("Bad soot nucleation mechanism");
	}

	switch (oxidationMechanism)
	{
		case OxidationMechanism::NONE:
			om = std::make_unique<OxidationModel_NONE>();
			break;
		case OxidationMechanism::LL:
			// TODO
			break;
		case OxidationMechanism::LEE_NEOH:
			// TODO
			break;
		case OxidationMechanism::NSC_NEOH:
			// TODO
			break;
		case OxidationMechanism::HACA:
			// TODO
			break;
		default:
			throw std::domain_error("Bad soot oxidation model");
	}

	/* create and return model ptr */
	switch (model)
	{
		case Model::MONO:
			return SootModel_MONO::getInstance(std::move(cm), std::move(gm), std::move(nm), std::move(om));
//		case Model::LOGN:
//			return
//		case Model::MOMIC:
//			return
//		case Model::QMOM:
//			return
//		case Model::SECT:
//			return
		default:
			throw std::domain_error("Bad soot model type");
	}
}
std::unique_ptr<soot::SootModel> soot::SootModelFactory::getModelUnique() const
{
	return std::unique_ptr<SootModel>(getModel());
}
std::shared_ptr<soot::SootModel> soot::SootModelFactory::getModelShared() const
{
	return std::shared_ptr<SootModel>(getModel());
}
