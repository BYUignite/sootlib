#ifndef COAGULATIONMODEL_MOMIC_H_
#define COAGULATIONMODEL_MOMIC_H_

#include <sootlib/state/State.h>

namespace soot {
class CoagulationModel_MOMIC {
public:
    [[nodiscard]] double getCoagulationRate(const State& state, int r) const;
};
}

#endif //COAGULATIONMODEL_MOMIC_H_
