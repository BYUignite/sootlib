#include "cantera/thermo.h"
#include "cantera/transport.h"

#include "sootlib/SootModelFactory.h"

using namespace Cantera;

int main(int argc, char** argv)
{
	// this is a demo that you can compile an example that has cantera and sootlib in it
	// THESE FILES ARE PLACEHOLDERS AND DON'T EXIST
	std::unique_ptr<ThermoPhase> gas(newPhase("gri30.cti", "gri30_mix"));

	auto factory = soot::SootModelFactory();

	return 0;
}
