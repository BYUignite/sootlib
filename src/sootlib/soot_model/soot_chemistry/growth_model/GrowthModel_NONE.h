#ifndef GROWTHMODEL_NONE_H
#define GROWTHMODEL_NONE_H

#include "GrowthModel.h"

namespace soot {
class GrowthModel_NONE : public GrowthModel {
public:
    [[nodiscard]] double getGrowthRate(const State& state, MassRateRatios& ratio) const override {
        return 0;
    }
    [[nodiscard]] GrowthMechanism getMechanism() const override {
        return GrowthMechanism::NONE;
    }

    ~GrowthModel_NONE() override = default;
};
}

#endif //GROWTHMODEL_NONE_H