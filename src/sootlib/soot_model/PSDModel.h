#ifndef MOMENTSOOTMODEL_H
#define MOMENTSOOTMODEL_H

#include "sootlib/SourceTerms.h"
#include "sootlib/state/State.h"

namespace soot {

enum class PSDMechanism { MONO, LOGN, MOMIC, QMOM, SECT };

class PSDModel {
public:
    [[nodiscard]] SourceTerms getSourceTermsVerbose(State& state, std::ostream& out) const {
        checkState(state);
        state.printInfo(out);
        SourceTerms sourceTerms = getSourceTermsImplementation(state, &out);
        return sourceTerms;
    }
    [[nodiscard]] SourceTerms getSourceTerms(State& state) const {
        return getSourceTermsImplementation(state, nullptr);
    }

    virtual ~PSDModel() = default;

private:
    // The meat function which calculates the source terms
    [[nodiscard]] virtual SourceTerms getSourceTermsImplementation(State& state, std::ostream* out) const = 0;

    // This function is called before getting the source terms and it's a place to enforce conditions on the state
    virtual void checkState(const State& state) const = 0;
};
}

#endif //MOMENTSOOTMODEL_H
