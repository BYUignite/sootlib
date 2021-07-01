#ifndef OXIDATIONMODEL_LL_H
#define OXIDATIONMODEL_LL_H

#include "OxidationModel.h"

namespace soot {
class OxidationModel_LL : public OxidationModel {
public:
    [[nodiscard]] double getOxidationRate(const State& state, MassRateRatios& ratio) const override;
    [[nodiscard]] OxidationMechanism getMechanism() const override {
        return OxidationMechanism::LL;
    }

    ~OxidationModel_LL() override = default;
};
}

#endif //OXIDATIONMODEL_LL_H
