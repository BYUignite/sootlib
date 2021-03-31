#include "MomentSootModelGenerator.h"

using namespace std;
using namespace soot;

void MomentSootModelGenerator::setModel(MomentModel model)
{
	this->model = model;
}
MomentSootModel* MomentSootModelGenerator::getModel() const
{
	/* create helper models */
	unique_ptr<CoagulationModel> cm = getCoagulationModel();
	unique_ptr<GrowthModel> gm = getGrowthModel();
	unique_ptr<NucleationModel> nm = getNucleationModel();
	unique_ptr<OxidationModel> om = getOxidationModel();

	/* create and return model ptr */
	switch (model)
	{
		case MomentModel::MONO:
			return SootModel_MONO::getInstance(move(cm),
			                                   move(gm),
			                                   move(nm),
			                                   move(om));
		case MomentModel::LOGN:
			return SootModel_LOGN::getInstance(move(cm),
			                                   move(gm),
			                                   move(nm),
			                                   move(om));
		case MomentModel::MOMIC:
			return SootModel_MOMIC::getInstance(move(cm),
			                                    move(gm),
			                                    move(nm),
			                                    move(om));
		case MomentModel::QMOM:
			return SootModel_QMOM::getInstance(move(cm),
			                                   move(gm),
			                                   move(nm),
			                                   move(om));
		default:
			throw domain_error("Bad soot model type");
	}
}
unique_ptr<MomentSootModel> MomentSootModelGenerator::getModelUnique() const
{
	return unique_ptr<MomentSootModel>(getModel());
}
shared_ptr<MomentSootModel> MomentSootModelGenerator::getModelShared() const
{
	return shared_ptr<MomentSootModel>(getModel());
}
MomentSootModelGenerator::MomentSootModelGenerator()
{
	model = MomentModel::MONO;
}
