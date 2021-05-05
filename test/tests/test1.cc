#include <iostream>
#include <fstream>

#include "sootlib/soot_model/generator/SootModelGenerator.h"

using namespace std;
using namespace soot;

/*
 * THIS IS A FILE MEANT FOR ROUGHLY TESTING ALL OF THE MODELS AT ONCE
 *
 * YOU CAN PROVIDE A FILENAME FOR THE RESULTS TO GO TO AS AN ARGUMENT, OR THE RESULTS WILL PRINT TO STD OUT
 *
 * THIS FILE WILL NOT TEST EACH MODEL THOROUGHLY
 */

int main(int argc, char** argv) {

    // ============== set stream for verbose output to either cout or a file ==============
    ofstream fout;
    ostream* out = &cout;
    if (argc > 1) {
        fout.open(argv[1]);
        out = &fout;
    }

    // ============== variables used for testing ==============
    auto generator = SootModelGenerator();
    auto state = State();
    unique_ptr<SootModel> sootModel;
    SourceTerms sourceTerms;

    // ============== set chemistry models ==============
    // TODO these might not be the best mechanisms to be testing with
    generator.setCoagulationMechanism(CoagulationMechanism::LL);
    generator.setGrowthMechanism(GrowthMechanism::LL);
    generator.setNucleationMechanism(NucleationMechanism::LL);
    generator.setOxidationMechanism(OxidationMechanism::LL);

    // ============== set state properties ==============
    // TODO I don't know appropriate values to fill in here
    state.resetMoments(2);
    state.setMoment(0, 20);
    state.setMoment(1, 20);

    state.setT(273);
    state.setP(101325);
    state.setRhoGas(10);
    state.setMWGas(25);
    state.setMuGas(2);

    state.setRhoSoot(10);

    state.setGasSpeciesFrac(GasSpecies::C2H2, 0.25);
    state.setGasSpeciesFrac(GasSpecies::O2, 0.25);
    state.setGasSpeciesFrac(GasSpecies::CO, 0.25);

    state.setPAHFrac(5, 0.25);

    // ============== begin moment tests ==============

    *out << "*********************************************" << endl;
    *out << "*             BEGIN MONO TEST               *" << endl;
    *out << "*********************************************" << endl << endl;

    generator.setModel(SootModelType::MONO);
    sootModel = generator.getModelUnique();

    sourceTerms = sootModel->getSourceTermsVerbose(state, *out);

    *out << "*********************************************" << endl;
    *out << "*            BEGIN LOGN TEST                *" << endl;
    *out << "*********************************************" << endl << endl;

    generator.setModel(SootModelType::LOGN);
    sootModel = generator.getModelUnique();

    sourceTerms = sootModel->getSourceTermsVerbose(state, *out);

    *out << "*********************************************" << endl;
    *out << "*            BEGIN MOMIC TEST               *" << endl;
    *out << "*********************************************" << endl << endl;

    generator.setModel(SootModelType::MOMIC);
    sootModel = generator.getModelUnique();

    sourceTerms = sootModel->getSourceTermsVerbose(state, *out);

    *out << "*********************************************" << endl;
    *out << "*           BEGIN QMOM TEST                 *" << endl;
    *out << "*********************************************" << endl << endl;

    generator.setModel(SootModelType::QMOM);
    sootModel = generator.getModelUnique();

    sourceTerms = sootModel->getSourceTermsVerbose(state, *out);

    // ============== begin sectional tests ==============
    state.resetSections(2);
    state.setSection(0, 0.5);
    state.setSection(1, 0.5);

    *out << "*********************************************" << endl;
    *out << "*            BEGIN SECT TEST                *" << endl;
    *out << "*********************************************" << endl << endl;

    generator.setModel(SootModelType::SECT);
    sootModel = generator.getModelUnique();

    sourceTerms = sootModel->getSourceTermsVerbose(state, *out);
}