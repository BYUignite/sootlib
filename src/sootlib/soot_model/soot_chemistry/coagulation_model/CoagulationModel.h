/**
 * Josh Bedwell - June 2021
 */

#ifndef COAGULATIONMODEL_H
#define COAGULATIONMODEL_H

#include "sootlib/state/State.h"

namespace soot {
/**
 * Interface used to calculate coagulation rate given a state and two masses
 */
class CoagulationModel {
public:
    /**
     * Unimplemented function to calculate a coagulation rate with the given parameters, not all of which might be used depending on the
     * implementation
     *
     * @param state
     * @param m1
     * @param m2
     * @return
     */
    [[nodiscard]] virtual double getCoagulationRate(const State& state, double m1, double m2) const = 0;
    /**
     * Unimplemented function to identify which mechanism the CoagulationModel uses
     * Used for some branching calculations
     *
     * @return
     */
    [[nodiscard]] virtual CoagulationMechanism getMechanism() const = 0;

    /**
     * Virtual deconstructor since interface will be used in the form of pointers
     */
    virtual ~CoagulationModel() = default;
};
}

#endif //COAGULATIONMODEL_H
