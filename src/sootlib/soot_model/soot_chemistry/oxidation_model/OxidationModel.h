#ifndef OXIDATIONMODEL_H
#define OXIDATIONMODEL_H

#include "sootlib/state/State.h"
#include "sootlib/ratio/MassRateRatios.h"

namespace soot {
class OxidationModel {
public:
    [[nodiscard]] virtual double getOxidationRate(const State& state, MassRateRatios& ratio) const = 0;
    [[nodiscard]] virtual OxidationMechanism getMechanism() const = 0;

    virtual ~OxidationModel() = default;
};
}

#endif //OXIDATIONMODEL_H
