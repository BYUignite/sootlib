#include "sootlib/MomentSootModelGenerator.h"

int main(int argc, char** argv)
{
	auto factory = soot::MomentSootModelGenerator();

	auto sootModel_1 = factory.getModelUnique();

	factory.setModel(soot::MomentModel::QMOM);
	factory.setNucleationMechanism(soot::NucleationMechanism::LL);
	factory.setGrowthMechanism(soot::GrowthMechanism::LL);
	factory.setOxidationMechanism(soot::OxidationMechanism::LL);
	factory.setCoagulationMechanism(soot::CoagulationMechanism::LL);
	factory.setNumSootVars(3);

	auto sootModel_2 = factory.getModelUnique();

	factory.setCoagulationMechanism(soot::CoagulationMechanism::FRENK);

	auto sootModel_3 = factory.getModelUnique();

	return 0;
}
