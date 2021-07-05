/**
 * Josh Bedwell - June 2021
 */

#ifndef COAGULATIONMODEL_FRENK_H
#define COAGULATIONMODEL_FRENK_H

#include "coagulationModel.h"

namespace soot {
class CoagulationModel_FRENK : public coagulationModel {
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
        return CoagulationMechanism::FRENK;
    }

    /**
     * Defines deconstructor behavior as default - required by coagulationModel
     */
    ~CoagulationModel_FRENK() override = default;
};
}

#endif //COAGULATIONMODEL_FRENK_H
