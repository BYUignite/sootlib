#ifndef OXIDATIONMODEL_HACA_H
#define OXIDATIONMODEL_HACA_H

#include "oxidationModel.h"

namespace soot {
class OxidationModel_HACA : public oxidationModel {
public:
    [[nodiscard]] double getOxidationRate(const State& state, MassRateRatios& ratio) const override;
    [[nodiscard]] OxidationMechanism getMechanism() const override {
        return OxidationMechanism::HACA;
    }

    ~OxidationModel_HACA() override = default;
};
}

#endif //OXIDATIONMODEL_HACA_H
