#include <iostream>

#include "TestTools.h"

#include "sootlib/soot_model/generator/SootModelGenerator.h"

using namespace std;
using namespace soot;

int main(int argc, char** argv) {
    auto generator = SootModelGenerator();
    generator.setModel(SootModelType::MOMIC);
    generator.setNucleationMechanism(NucleationMechanism::LL);
    generator.setGrowthMechanism(GrowthMechanism::LL);
    generator.setOxidationMechanism(OxidationMechanism::LL);
    generator.setCoagulationMechanism(CoagulationMechanism::LL);
    auto model = generator.getModelUnique();

    auto state = State();
    state.resetMoments(1);
    state.setMoment(0, 1.0e17);
    state.setT(1500);
    state.setP(101325);
    state.setRhoGas(0.08);
    state.setMWGas(28.4156);
    state.setMuGas(1.0e-5);
    state.setGasSpeciesFrac(GasSpecies::C2H2, 0.2);
    state.setGasSpeciesFrac(GasSpecies::O2, 0.2);

    cout << "Starting model..." << endl;
    auto sourceTerms = model->getSourceTermsVerbose(state, cout);
    cout << "The model did not crash" << endl;

    return 0;
}
