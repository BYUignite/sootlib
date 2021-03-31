#include "MomentSootModelGenerator.h"

using namespace soot;

void MomentSootModelGenerator::setModel(MomentModel model)
{
	this->model = model;
}
MomentSootModel* MomentSootModelGenerator::getModel() const
{
	/* create helper models */
	std::unique_ptr<CoagulationModel> cm = getCoagulationModel();
	std::unique_ptr<GrowthModel> gm = getGrowthModel();
	std::unique_ptr<NucleationModel> nm = getNucleationModel();
	std::unique_ptr<OxidationModel> om = getOxidationModel();

	/* create and return model ptr */
	switch (model)
	{
		case MomentModel::MONO:
			return SootModel_MONO::getInstance(std::move(cm),
			                                   std::move(gm),
			                                   std::move(nm),
			                                   std::move(om));
		case MomentModel::LOGN:
			return SootModel_LOGN::getInstance(std::move(cm),
			                                   std::move(gm),
			                                   std::move(nm),
			                                   std::move(om));
		case MomentModel::MOMIC:
			return SootModel_MOMIC::getInstance(std::move(cm),
			                                    std::move(gm),
			                                    std::move(nm),
			                                    std::move(om));
		case MomentModel::QMOM:
			return SootModel_QMOM::getInstance(std::move(cm),
			                                   std::move(gm),
			                                   std::move(nm),
			                                   std::move(om));
		default:
			throw std::domain_error("Bad soot model type");
	}
}
std::unique_ptr<MomentSootModel> MomentSootModelGenerator::getModelUnique() const
{
	return std::unique_ptr<MomentSootModel>(getModel());
}
std::shared_ptr<MomentSootModel> MomentSootModelGenerator::getModelShared() const
{
	return std::shared_ptr<MomentSootModel>(getModel());
}
MomentSootModelGenerator::MomentSootModelGenerator()
{
	model = MomentModel::MONO;
}
