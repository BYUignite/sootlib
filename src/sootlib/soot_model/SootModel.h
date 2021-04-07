#ifndef MOMENTSOOTMODEL_H
#define MOMENTSOOTMODEL_H

#include "sootlib/SourceTerms.h"
#include "sootlib/state/State.h"

namespace soot {
enum class SootModelType { MONO, LOGN, MOMIC, QMOM, SECT };
class SootModel {
public:
    [[nodiscard]] virtual SourceTerms getSourceTerms(State& state) const = 0;

    virtual ~SootModel() = default;
};
}

#endif //MOMENTSOOTMODEL_H
