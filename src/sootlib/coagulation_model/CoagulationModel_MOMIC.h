#ifndef COAGULATIONMODEL_MOMIC_H_
#define COAGULATIONMODEL_MOMIC_H_

#include <sootlib/state/InputState.h>

namespace soot {
class CoagulationModel_MOMIC {
public:
    [[nodiscard]] double getCoagulationRate(const InputState& state, int r) const;
};
}

#endif //COAGULATIONMODEL_MOMIC_H_
