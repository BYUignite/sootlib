#include <iostream>

#include "sootlib/soot_model/generator/SootModelGenerator.h"

using namespace soot;
using namespace std;

int main(int argc, char** argv) {
    /* Create a soot model generator */

    // this generator can make moment based soot psdModels
    auto generator = SootModelGenerator();

    /* Create a default soot model */

    // this gives the model as a unique smart pointer
    auto sootModel = generator.getModelUnique();

    /* Get source terms given a state */

    auto state = State();

    // set the values of the moments to what we want
    state.resetMoments(2);
    state.setMoment(0, 100);
    state.setMoment(1, 55.5);
//    state.setMwGas(200.1);
    state.setGasSpeciesFrac(GasSpecies::O2, 1.0);
    state.setP(21);
    state.setT(100);

//    auto sourceTerms = sootModel->getSourceTermsImpl(state);
//
//    // TODO it looks like there is some value in the state that needs to be set not to 0 becuase we are getting NAN
//    /* Print the values we got */
//    cout << "Soot source terms:" << endl;
//    for (auto it = sourceTerms.sootTermsBegin(); it != sourceTerms.sootTermsEnd(); it++)
//        cout << *it << endl;
//
//    cout << endl << "Gas source terms:" << endl;
//    for (auto it = sourceTerms.gasTermsBegin(); it != sourceTerms.gasTermsEnd(); it++)
//        cout << "Gas species (code): " << int(it->first) << " Term: " << it->second << endl;

    return 0;
}
