/**
 * Josh Bedwell - June 2021
 */

#ifndef COAGULATIONMODEL_NONE_H
#define COAGULATIONMODEL_NONE_H

#include "coagulationModel.h"

namespace soot {
class CoagulationModel_NONE : public coagulationModel {
/**
 * The default implementation of coagulationModel interface
 */
public:
    /**
     * Always returns 0 for coagulation rate - required by coagulationModel
     *
     * @param state
     * @param m1
     * @param m2
     * @return
     */
    [[nodiscard]] double getCoagulationRate(const State& state, double m1, double m2) const override {
        return 0;
    }
    /**
     * Reports mechanism type - requried by coagulationModel
     *
     * @return
     */
    [[nodiscard]] CoagulationMechanism getMechanism() const override {
        return CoagulationMechanism::NONE;
    }

    /**
     * Defines deconstructor behavior as default - required by coagulationModel
     */
    ~CoagulationModel_NONE() override = default;
};
}

#endif //COAGULATIONMODEL_NONE_H
