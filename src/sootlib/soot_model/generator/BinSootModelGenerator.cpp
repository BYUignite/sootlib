#include "BinSootModelGenerator.h"

using namespace soot;

BinSootModelGenerator::BinSootModelGenerator()
{
	model = BinModel::SECT;
}
void BinSootModelGenerator::setModel(soot::BinModel model)
{
	this->model = model;
}
BinSootModel* BinSootModelGenerator::getModel() const
{
	/* create helper models */
	std::unique_ptr<CoagulationModel> cm;
	std::unique_ptr<GrowthModel> gm;
	std::unique_ptr<NucleationModel> nm;
	std::unique_ptr<OxidationModel> om;

	switch (model)
	{
		case BinModel::SECT:
			return SootModel_SECT::getInstance(std::move(cm),
									  std::move(gm),
									  std::move(nm),
									  std::move(om));
		default:
			throw std::domain_error("Bad soot model type");
	}
}
std::unique_ptr<BinSootModel> BinSootModelGenerator::getModelUnique() const
{
	return std::unique_ptr<BinSootModel>(getModel());
}
std::shared_ptr<BinSootModel> BinSootModelGenerator::getModelShared() const
{
	return std::shared_ptr<BinSootModel>(getModel());
}
