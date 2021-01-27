#include "sootlib/SootModelFactory.h"

int main(int argc, char** argv)
{
	soot::SootModelFactory factory = soot::SootModelFactory();
	factory.setModel(soot::Model::MONO);
	factory.setNucleationMechanism(soot::NucleationMechanism::NONE);
	factory.setGrowthMechanism(soot::GrowthMechanism::NONE);
	factory.setOxidationMechanism(soot::OxidationMechanism::NONE);
	factory.setCoagulationMechanism(soot::CoagulationMechanism::NONE);

	auto sootModel = factory.getModelUnique();

	return 0;
}
