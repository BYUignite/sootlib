#include "sootlib/soot_model/generator/BinSootModelGenerator.h"

int main(int argc, char** argv)
{
	/* Create a soot model generator */

	// this generator can make bin based soot models
	auto generator = soot::BinSootModelGenerator();

	/* Create a default soot model */

	// this gives the model as a unique smart pointer
	auto sootModel = generator.getModelUnique();

	/* Get source terms given a state */

	auto state = soot::BinState();
	auto sourceTerms = sootModel->getSourceTerms(state);

	return 0;
}