#ifndef GROWTHMODEL_H
#define GROWTHMODEL_H

#include "src/state.h"

namespace soot {
class growthModel {
public:
    [[nodiscard]] virtual double getGrowthRate(const state& state, MassRateRatios& ratio) const = 0;
    [[nodiscard]] virtual growthMech getMechanism() const = 0;

    virtual ~growthModel() = default;
};
}

#endif //GROWTHMODEL_H
