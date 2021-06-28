/**
 * Josh Bedwell - June 2021
 */

#ifndef COAGULATIONMODEL_NONE_H
#define COAGULATIONMODEL_NONE_H

#include "CoagulationModel.h"

namespace soot {
class CoagulationModel_NONE : public CoagulationModel {
/**
 * The default implementation of CoagulationModel interface
 */
public:
    /**
     * Always returns 0 for coagulation rate - required by CoagulationModel
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
     * Reports mechanism type - requried by CoagulationModel
     *
     * @return
     */
    [[nodiscard]] CoagulationMechanism getMechanism() const override {
        return CoagulationMechanism::NONE;
    }

    /**
     * Defines deconstructor behavior as default - required by CoagulationModel
     */
    ~CoagulationModel_NONE() override = default;
};
}

#endif //COAGULATIONMODEL_NONE_H
