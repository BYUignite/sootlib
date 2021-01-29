#include "cantera/IdealGasMix.h"
#include "sootlib/SootModelFactory.h"

int main(int argc, char** argv)
{
	// this is a demo that you can compile an example that has cantera and sootlib in it
	auto gas = Cantera::IdealGasMix("this file doesn't exist");
	auto factory = soot::SootModelFactory();

	return 0;
}
