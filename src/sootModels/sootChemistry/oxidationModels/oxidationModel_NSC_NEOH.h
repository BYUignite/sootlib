#ifndef OXIDATIONMODEL_NSC_NEOH_H
#define OXIDATIONMODEL_NSC_NEOH_H

#include "oxidationModel.h"

namespace soot {
class OxidationModel_NSC_NEOH : public oxidationModel {
public:
    [[nodiscard]] double getOxidationRate(const State& state, MassRateRatios& ratio) const override;
    [[nodiscard]] OxidationMechanism getMechanism() const override {
        return OxidationMechanism::NSC_NEOH;
    }

    ~OxidationModel_NSC_NEOH() override = default;
};
}

#endif //OXIDATIONMODEL_NSC_NEOH_H
