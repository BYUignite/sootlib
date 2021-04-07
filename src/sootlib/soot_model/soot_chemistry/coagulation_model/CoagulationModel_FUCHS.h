#ifndef COAGULATIONMODEL_FUCHS_H
#define COAGULATIONMODEL_FUCHS_H

#include "CoagulationModel.h"

namespace soot {
class CoagulationModel_FUCHS : public CoagulationModel {
public:
    [[nodiscard]] double getCoagulationRate(const State& state, double m1, double m2) const override;
    [[nodiscard]] CoagulationMechanism getMechanism() const override {
        return CoagulationMechanism::FUCHS;
    }

    ~CoagulationModel_FUCHS() override = default;
};
}

#endif //COAGULATIONMODEL_FUCHS_H
