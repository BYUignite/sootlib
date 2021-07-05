#ifndef PSDMODEL_H
#define PSDMODEL_H

#include "src/state.h"
#include "src/constants.h"

namespace soot {
    
/**
 * Interface for a particle size distribution (PSD) Model
 */
class psdModel {

public:
    /**
     * An implemented public function which calls getSourceTermsImplementation and calculates source terms using an outstream for debugging purposes
     * Calls checkState which is unimplemented with the state before doing the calculation to verify the calculation is possible
     *
     * @param state
     * @param out
     * @return
     */
     sourceTerms getSourceTermsVerbose(state& state, std::ostream& out) const {
        checkState(state);
        state.printInfo(out);
        sourceTerms sourceTerms = getSourceTermsImplementation(state, &out);
        return sourceTerms;
    }
    /**
     * An implemented public function which calls getSourceTermsImplementation and calculates source terms
     * Calls checkState which is unimplemented with the state before doing the calculation to verify the calculation is possible
     * Uses a null pointer for the debug outstream
     * This is the function which will be called by the user to provide functionality
     *
     * @param state
     * @return
     */
     sourceTerms getSourceTerms(state& state) const {
        checkState(state);
        return getSourceTermsImplementation(state, nullptr);
    }

    /**
     * Virtual deconstructor since interface will be used in the form of pointers
     */
    virtual ~psdModel() = default;

private:
    /**
     * Unimplemented function which uses the provided state to calculate source terms and return them in a SourceTerms object
     *
     * @param state
     * @param out
     * @return
     */
     virtual sourceTerms getSourceTermsImplementation(state& state, std::ostream* out) const = 0;

    /**
     * Unimplemented function which throws exceptions if it is impossible to calculate source terms with the given state
     *
     * @param state
     */
    virtual void checkState(const state& state) const = 0;
};
}

#endif //PSDMODEL_H
