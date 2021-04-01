#ifndef OXIDATIONMODEL_H
#define OXIDATIONMODEL_H

#include "sootlib/state/MomentState.h"
#include "sootlib/MassRateRatios.h"

namespace soot {
class OxidationModel {
public:
    [[nodiscard]] virtual double getOxidationRate(const MomentState& state, MassRateRatios& ratio) const = 0;
    [[nodiscard]] virtual OxidationMechanism getMechanism() const = 0;

    virtual ~OxidationModel() = default;
};
}

#endif //OXIDATIONMODEL_H
