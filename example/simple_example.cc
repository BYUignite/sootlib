#include <iostream>

#include "sootlib/soot_model/generator/SootModelGenerator.h"

using namespace std;
using namespace soot;

int main(int argc, char** argv) {
    /* Create a soot model generator */

    // this generator can make moment based soot psd_models
    auto generator = SootModelGenerator();

    /* Create a default soot model */

    // this gives the model as a unique smart pointer
    auto sootModel = generator.getModelUnique();

    /* Get source terms given a state */

    auto state = State();
    // the default mono model requires at least 2 soot moments
    state.resetMoments(2);
    auto sourceTerms = sootModel->getSourceTerms(state);

    sourceTerms = sootModel->getSourceTermsVerbose(state, cout);

    return 0;
}
