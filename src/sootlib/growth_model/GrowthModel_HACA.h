#ifndef GROWTHMODEL_HACA_H
#define GROWTHMODEL_HACA_H

#include "sootlib/growth_model/GrowthModel.h"

namespace soot {
class GrowthModel_HACA : public GrowthModel {
public:
    [[nodiscard]] double getGrowthRate(const MomentState& state, MassRateRatios& ratio) const override;
    [[nodiscard]] GrowthMechanism getMechanism() const override {
        return GrowthMechanism::HACA;
    }

    ~GrowthModel_HACA() override = default;
};
}

#endif //GROWTHMODEL_HACA_H
