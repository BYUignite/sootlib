#ifndef COAGULATIONMODEL_FRENK_H
#define COAGULATIONMODEL_FRENK_H

#include "CoagulationModel.h"

namespace soot {
class CoagulationModel_FRENK : public CoagulationModel {
public:
    [[nodiscard]] double getCoagulationRate(const State& state, double m1, double m2) const override;
    [[nodiscard]] CoagulationMechanism getMechanism() const override {
        return CoagulationMechanism::FRENK;
    }

    ~CoagulationModel_FRENK() override = default;
};
}

#endif //COAGULATIONMODEL_FRENK_H
