#ifndef GROWTHMODEL_LIN_H
#define GROWTHMODEL_LIN_H

#include "growthModel.h"

namespace soot {
class GrowthModel_LIN : public growthModel {
public:
    [[nodiscard]] double getGrowthRate(const State& state, MassRateRatios& ratio) const override;
    [[nodiscard]] GrowthMechanism getMechanism() const override {
        return GrowthMechanism::LIN;
    }

    ~GrowthModel_LIN() override = default;
};
}

#endif //GROWTHMODEL_LIN_H
