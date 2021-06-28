/**
 * Josh Bedwell - June 2021
 *
 * This file contains the interface for the core functionality of sootlib
 */

#ifndef MOMENTSOOTMODEL_H
#define MOMENTSOOTMODEL_H

#include "sootlib/SourceTerms.h"
#include "sootlib/state/State.h"

namespace soot {
/**
 * enum used for specifying PSD mechanisms, especially in the PSD generator
 */
enum class PSDMechanism { MONO, LOGN, MOMIC, QMOM, SECT };

class PSDModel {
// TODO I'm not actually sure that acronym is correct
/**
 * Interface for a Partical Size Distribution (PSD) Model
 */
public:
    /**
     * An implemented public function which calls getSourceTermsImplementation and calculates source terms using an outstream for debugging purposes
     * Calls checkState which is unimplemented with the state before doing the calculation to verify the calculation is possible
     *
     * @param state
     * @param out
     * @return
     */
    [[nodiscard]] SourceTerms getSourceTermsVerbose(State& state, std::ostream& out) const {
        checkState(state);
        state.printInfo(out);
        SourceTerms sourceTerms = getSourceTermsImplementation(state, &out);
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
    [[nodiscard]] SourceTerms getSourceTerms(State& state) const {
        checkState(state);
        return getSourceTermsImplementation(state, nullptr);
    }

    /**
     * Virtual deconstructor since interface will be used in the form of pointers
     */
    virtual ~PSDModel() = default;

private:
    /**
     * Unimplemented function which uses the provided state to calculate source terms and return them in a SourceTerms object
     *
     * @param state
     * @param out
     * @return
     */
    [[nodiscard]] virtual SourceTerms getSourceTermsImplementation(State& state, std::ostream* out) const = 0;

    /**
     * Unimplemented function which throws exceptions if it is impossible to calculate source terms with the given state
     *
     * @param state
     */
    virtual void checkState(const State& state) const = 0;
};
}

#endif //MOMENTSOOTMODEL_H
