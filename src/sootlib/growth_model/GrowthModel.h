#ifndef GROWTHMODEL_H
#define GROWTHMODEL_H

#include "sootlib/state/InputState.h"
#include "sootlib/MassRateRatios.h"

namespace soot {
class GrowthModel {
public:
    [[nodiscard]] virtual double getGrowthRate(const InputState& state, MassRateRatios& ratio) const = 0;
    [[nodiscard]] virtual GrowthMechanism getMechanism() const = 0;

    virtual ~GrowthModel() = default;
};
}

#endif //GROWTHMODEL_H
