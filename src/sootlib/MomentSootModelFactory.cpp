#include "MomentSootModelFactory.h"
void soot::MomentSootModelFactory::setModel(soot::MomentModel model)
{
	this->model = model;
}
void soot::MomentSootModelFactory::setNucleationMechanism(soot::NucleationMechanism mechanism)
{
	nucleationMechanism = mechanism;
}
void soot::MomentSootModelFactory::setGrowthMechanism(soot::GrowthMechanism mechanism)
{
	growthMechanism = mechanism;
}
void soot::MomentSootModelFactory::setOxidationMechanism(soot::OxidationMechanism mechanism)
{
	oxidationMechanism = mechanism;
}
void soot::MomentSootModelFactory::setCoagulationMechanism(soot::CoagulationMechanism mechanism)
{
	coagulationMechanism = mechanism;
}
soot::MomentSootModel* soot::MomentSootModelFactory::getModel() const
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
			cm = std::make_unique<CoagulationModel_LL>();
			break;
		case CoagulationMechanism::FUCHS:
			cm = std::make_unique<CoagulationModel_FUCHS>();
			break;
		case CoagulationMechanism::FRENK:
			cm = std::make_unique<CoagulationModel_FRENK>();
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
			gm = std::make_unique<GrowthModel_LL>();
			break;
		case GrowthMechanism::LIN:
			gm = std::make_unique<GrowthModel_LIN>();
			break;
		case GrowthMechanism::HACA:
			gm = std::make_unique<GrowthModel_HACA>();
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
			nm = std::make_unique<NucleationModel_LL>();
			break;
		case NucleationMechanism::LIN:
			nm = std::make_unique<NucleationModel_LIN>();
			break;
		case NucleationMechanism::PAH:
			nm = std::make_unique<NucleationModel_PAH>();
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
			om = std::make_unique<OxidationModel_LL>();
			break;
		case OxidationMechanism::LEE_NEOH:
			om = std::make_unique<OxidationModel_LEE_NEOH>();
			break;
		case OxidationMechanism::NSC_NEOH:
			om = std::make_unique<OxidationModel_NSC_NEOH>();
			break;
		case OxidationMechanism::HACA:
			om = std::make_unique<OxidationModel_HACA>();
			break;
		default:
			throw std::domain_error("Bad soot oxidation model");
	}

	/* create and return model ptr */
	switch (model)
	{
		case MomentModel::MONO:
			return SootModel_MONO::getInstance(std::move(cm),
									  std::move(gm),
									  std::move(nm),
									  std::move(om));
//		case MomentModel::LOGN:
//			return
//		case MomentModel::MOMIC:
//			return
//		case MomentModel::QMOM:
//			return
		default:
			throw std::domain_error("Bad soot model type");
	}
}
std::unique_ptr<soot::MomentSootModel> soot::MomentSootModelFactory::getModelUnique() const
{
	return std::unique_ptr<MomentSootModel>(getModel());
}
std::shared_ptr<soot::MomentSootModel> soot::MomentSootModelFactory::getModelShared() const
{
	return std::shared_ptr<MomentSootModel>(getModel());
}
soot::MomentSootModelFactory::MomentSootModelFactory()
{
	model = MomentModel::MONO;
	nucleationMechanism = NucleationMechanism::NONE;
	growthMechanism = GrowthMechanism::NONE;
	oxidationMechanism = OxidationMechanism::NONE;
	coagulationMechanism = CoagulationMechanism::NONE;
}
