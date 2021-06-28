#include "sootlib/soot_model/generator/SootModelGenerator.h"

using namespace soot;
using namespace std;

int main(int argc, char** argv) {
    /*
     * There are 2 kinds of soot psd_models: bin and moment based
     * There is a generator for each kind
     */

    SootModelGenerator momentModelGenerator = SootModelGenerator();

    /*
     * At any time you can get a soot model from a generator as either a:
     * raw pointer
     * smart unique pointer
     * smart shared pointer
     */

    PSDModel* rawMomentModel = momentModelGenerator.getModel();
    unique_ptr<PSDModel> uniqueMomentModel = momentModelGenerator.getModelUnique();
    shared_ptr<PSDModel> sharedMomentModel = momentModelGenerator.getModelShared();

    /*
     * Any soot model is going to have a coagultion model, growth model, nucleation model, and oxidation model
     *
     * By default these are all set to NONE, meaning they essentially won't be accounted for
     * These can be set in the generator and then it will produce soot psd_models using those supporting psd_models
     */

    momentModelGenerator.setCoagulationMechanism(CoagulationMechanism::LL);
    momentModelGenerator.setGrowthMechanism(GrowthMechanism::LIN);
    momentModelGenerator.setNucleationMechanism(NucleationMechanism::PAH);
    momentModelGenerator.setOxidationMechanism(OxidationMechanism::NSC_NEOH);

    // new model is using these supporting psd_models
    rawMomentModel = momentModelGenerator.getModel();

    /*
     * There are different kinds of bin and moment soot psd_models
     * This can also be set in the generator
     *
     * The current default moment based model is MONO
     * The current default bin based model is SECT
     */

    momentModelGenerator.setPSDModel(PSDMechanism::QMOM);

    rawMomentModel = momentModelGenerator.getModel();

    return 0;
}
