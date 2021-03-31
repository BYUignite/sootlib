#include "BinSootModelGenerator.h"

using namespace std;
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
	unique_ptr<CoagulationModel> cm;
	unique_ptr<GrowthModel> gm;
	unique_ptr<NucleationModel> nm;
	unique_ptr<OxidationModel> om;

	switch (model)
	{
		case BinModel::SECT:
			return SootModel_SECT::getInstance(move(cm),
									  move(gm),
									  move(nm),
									  move(om));
		default:
			throw domain_error("Bad soot model type");
	}
}
unique_ptr<BinSootModel> BinSootModelGenerator::getModelUnique() const
{
	return unique_ptr<BinSootModel>(getModel());
}
shared_ptr<BinSootModel> BinSootModelGenerator::getModelShared() const
{
	return shared_ptr<BinSootModel>(getModel());
}
