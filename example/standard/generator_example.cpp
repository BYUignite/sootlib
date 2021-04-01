#include "sootlib/soot_model/generator/SootModelGenerator.h"

int main(int argc, char** argv) {
    /*
     * There are 2 kinds of soot models: bin and moment based
     * There is a generator for each kind
     */

    soot::SootModelGenerator momentModelGenerator = soot::SootModelGenerator();

    /*
     * At any time you can get a soot model from a generator as either a:
     * raw pointer
     * smart unique pointer
     * smart shared pointer
     */

    soot::SootModel* rawMomentModel = momentModelGenerator.getModel();
    std::unique_ptr<soot::SootModel> uniqueMomentModel = momentModelGenerator.getModelUnique();
    std::shared_ptr<soot::SootModel> sharedMomentModel = momentModelGenerator.getModelShared();

    /*
     * Any soot model is going to have a coagultion model, growth model, nucleation model, and oxidation model
     *
     * By default these are all set to NONE, meaning they essentially won't be accounted for
     * These can be set in the generator and then it will produce soot models using those supporting models
     */

    momentModelGenerator.setCoagulationMechanism(soot::CoagulationMechanism::LL);
    momentModelGenerator.setGrowthMechanism(soot::GrowthMechanism::LIN);
    momentModelGenerator.setNucleationMechanism(soot::NucleationMechanism::PAH);
    momentModelGenerator.setOxidationMechanism(soot::OxidationMechanism::NSC_NEOH);

    // new model is using these supporting models
    rawMomentModel = momentModelGenerator.getModel();

    /*
     * There are different kinds of bin and moment soot models
     * This can also be set in the generator
     *
     * The current default moment based model is MONO
     * The current default bin based model is SECT
     */

    momentModelGenerator.setModel(soot::SootModelType::QMOM);

    rawMomentModel = momentModelGenerator.getModel();

    return 0;
}
