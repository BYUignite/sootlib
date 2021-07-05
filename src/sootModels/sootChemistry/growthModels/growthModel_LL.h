#ifndef GROWTHMODEL_LL_H
#define GROWTHMODEL_LL_H

#include "growthModel.h"

namespace soot {
class GrowthModel_LL : public growthModel {
public:
    [[nodiscard]] double getGrowthRate(const State& state, MassRateRatios& ratio) const override;
    [[nodiscard]] GrowthMechanism getMechanism() const override {
        return GrowthMechanism::LL;
    }

    ~GrowthModel_LL() override = default;
};
}

#endif //GROWTHMODEL_LL_H
