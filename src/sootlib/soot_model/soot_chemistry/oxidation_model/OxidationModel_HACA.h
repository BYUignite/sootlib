#ifndef OXIDATIONMODEL_HACA_H
#define OXIDATIONMODEL_HACA_H

#include "OxidationModel.h"

namespace soot {
class OxidationModel_HACA : public OxidationModel {
public:
    [[nodiscard]] double getOxidationRate(const State& state, MassRateRatios& ratio) const override;
    [[nodiscard]] OxidationMechanism getMechanism() const override {
        return OxidationMechanism::HACA;
    }

    ~OxidationModel_HACA() override = default;
};
}

#endif //OXIDATIONMODEL_HACA_H
