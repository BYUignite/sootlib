#ifndef OXIDATIONMODEL_NONE_H
#define OXIDATIONMODEL_NONE_H

#include "oxidationModel.h"

namespace soot {
class OxidationModel_NONE : public oxidationModel {
public:
    [[nodiscard]] double getOxidationRate(const State& state, MassRateRatios& ratio) const override {
        return 0;
    }
    [[nodiscard]] OxidationMechanism getMechanism() const override {
        return OxidationMechanism::NONE;
    }

    ~OxidationModel_NONE() override = default;
};
}

#endif //OXIDATIONMODEL_NONE_H
