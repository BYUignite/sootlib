#ifndef MOMENTSOOTMODEL_H
#define MOMENTSOOTMODEL_H

#include "sootlib/SourceTerms.h"
#include "sootlib/state/State.h"

namespace soot {

enum class SootModelType { MONO, LOGN, MOMIC, QMOM, SECT };

class SootModel {
public:
    [[nodiscard]] SourceTerms getSourceTermsVerbose(State& state, std::ostream& out) const {
        checkState(state);
        state.printInfo(out);
        SourceTerms sourceTerms = getSourceTermsImpl(state, &out);
        return sourceTerms;
    }
    [[nodiscard]] SourceTerms getSourceTerms(State& state) const {
        checkState(state);
        return getSourceTermsImpl(state, nullptr);
    }

    virtual ~SootModel() = default;

private:
    // The meat function which calculates the source terms
    [[nodiscard]] virtual SourceTerms getSourceTermsImpl(State& state, std::ostream* out) const = 0;

    // This function is called before getting the source terms and it's a place to enforce conditions on the state
    virtual void checkState(const State& state) const = 0;
};
}

#endif //MOMENTSOOTMODEL_H
