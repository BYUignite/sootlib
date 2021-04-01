#ifndef GROWTHMODEL_LIN_H
#define GROWTHMODEL_LIN_H

#include "sootlib/growth_model/GrowthModel.h"

namespace soot {
class GrowthModel_LIN : public GrowthModel {
public:
    [[nodiscard]] double getGrowthRate(const InputState& state, MassRateRatios& ratio) const override;
    [[nodiscard]] GrowthMechanism getMechanism() const override {
        return GrowthMechanism::LIN;
    }

    ~GrowthModel_LIN() override = default;
};
}

#endif //GROWTHMODEL_LIN_H
