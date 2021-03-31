#ifndef MOMENTSOOTMODEL_H
#define MOMENTSOOTMODEL_H

#include "sootlib/SourceTerms.h"
#include "sootlib/state/MomentState.h"

namespace soot {
class MomentSootModel {
public:
    [[nodiscard]] virtual SourceTerms getSourceTerms(MomentState& state) const = 0;

    virtual ~MomentSootModel() = default;
};
}

#endif //MOMENTSOOTMODEL_H
