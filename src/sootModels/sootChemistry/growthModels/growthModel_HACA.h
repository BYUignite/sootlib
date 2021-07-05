#ifndef GROWTHMODEL_HACA_H
#define GROWTHMODEL_HACA_H

#include "growthModel.h"

namespace soot {
class GrowthModel_HACA : public growthModel {
public:
    [[nodiscard]] double getGrowthRate(const State& state, MassRateRatios& ratio) const override;
    [[nodiscard]] GrowthMechanism getMechanism() const override {
        return GrowthMechanism::HACA;
    }

    ~GrowthModel_HACA() override = default;
};
}

#endif //GROWTHMODEL_HACA_H
