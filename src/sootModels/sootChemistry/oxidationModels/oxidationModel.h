#ifndef OXIDATIONMODEL_H
#define OXIDATIONMODEL_H

#include "src/state.h"

namespace soot {
class oxidationModel {
public:
    [[nodiscard]] virtual double getOxidationRate(const state& state, MassRateRatios& ratio) const = 0;
    [[nodiscard]] virtual oxidationMechanism getMechanism() const = 0;

    virtual ~oxidationModel() = default;
};
}

#endif //OXIDATIONMODEL_H
