/**
 * Josh Bedwell - June 2021
 */

#ifndef COAGULATIONMODEL_FUCHS_H
#define COAGULATIONMODEL_FUCHS_H

#include "coagulationModel.h"

namespace soot {
class CoagulationModel_FUCHS : public coagulationModel {
/**
 * Implementation of coagulationModel interface
 */
public:
    /**
     * Calculates coagulation rate - required by coagulationModel
     *
     * @param state
     * @param m1
     * @param m2
     * @return
     */
    [[nodiscard]] double getCoagulationRate(const State& state, double m1, double m2) const override;
    /**
     * Reports mechanism type - requried by coagulationModel
     *
     * @return
     */
    [[nodiscard]] CoagulationMechanism getMechanism() const override {
        return CoagulationMechanism::FUCHS;
    }

    /**
     * Defines deconstructor behavior as default - required by coagulationModel
     */
    ~CoagulationModel_FUCHS() override = default;
};
}

#endif //COAGULATIONMODEL_FUCHS_H
