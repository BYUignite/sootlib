#ifndef OXIDATIONMODEL_NSC_NEOH_H
#define OXIDATIONMODEL_NSC_NEOH_H

#include "sootlib/oxidation_model/OxidationModel.h"

namespace soot {
class OxidationModel_NSC_NEOH : public OxidationModel {
public:
    [[nodiscard]] double getOxidationRate(const InputState& state, MassRateRatios& ratio) const override;
    [[nodiscard]] OxidationMechanism getMechanism() const override {
        return OxidationMechanism::NSC_NEOH;
    }

    ~OxidationModel_NSC_NEOH() override = default;
};
}

#endif //OXIDATIONMODEL_NSC_NEOH_H
