#include "sootlib/SootModelFactory.h"

int main(int argc, char** argv)
{
	auto factory = soot::SootModelFactory();

	auto sootModel_1 = factory.getModelUnique();

	factory.setModel(soot::Model::QMOM);
	factory.setNucleationMechanism(soot::NucleationMechanism::LL);
	factory.setGrowthMechanism(soot::GrowthMechanism::LL);
	factory.setOxidationMechanism(soot::OxidationMechanism::LL);
	factory.setCoagulationMechanism(soot::CoagulationMechanism::LL);

	auto sootModel_2 = factory.getModelUnique();

	return 0;
}
