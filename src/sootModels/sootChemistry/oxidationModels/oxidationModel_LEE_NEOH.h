#ifndef OXIDATIONMODEL_LEE_NEOH_H
#define OXIDATIONMODEL_LEE_NEOH_H

#include "oxidationModel.h"

namespace soot {
class OxidationModel_LEE_NEOH : public oxidationModel {
public:
    [[nodiscard]] double getOxidationRate(const State& state, MassRateRatios& ratio) const override;
    [[nodiscard]] OxidationMechanism getMechanism() const override {
        return OxidationMechanism::LEE_NEOH;
    }

    ~OxidationModel_LEE_NEOH() override = default;
};
}

#endif //OXIDATIONMODEL_LEE_NEOH_H
