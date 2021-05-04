#ifndef MOMENTSOOTMODEL_H
#define MOMENTSOOTMODEL_H

#include "sootlib/SourceTerms.h"
#include "sootlib/state/State.h"

namespace soot {
enum class SootModelType { MONO, LOGN, MOMIC, QMOM, SECT };
class SootModel {
public:
    [[nodiscard]] SourceTerms getSourceTermsVerbose(State& state, std::ostream& out) const {
        state.printIssues(out);
        return getSourceTermsImpl(state, &out);
    }
    [[nodiscard]] SourceTerms getSourceTerms(State& state) const {
        return getSourceTermsImpl(state, nullptr);
    }

    virtual ~SootModel() = default;

private:
    [[nodiscard]] virtual SourceTerms getSourceTermsImpl(State& state, std::ostream* out) const = 0;
};
}

#endif //MOMENTSOOTMODEL_H
