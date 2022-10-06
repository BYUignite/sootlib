#pragma once

#include "state.h"
#include "constants.h"

namespace soot {

/**
 * Interface used to calculate coagulation rate given a state and two masses
 */
class coagulationModel {

//////////////// DATA MEMBERS /////////////////////

private:

//////////////// MEMBER FUNCTIONS /////////////////

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
     virtual double getCoagulationSootRate(const state& state, double m1, double m2) const = 0;

//////////////// CONSTRUCTOR FUNCTIONS ////////////

public:

    coagulationModel() = default;
    virtual ~coagulationModel() = default;      // Virtual deconstructor since interface will be used in the form of pointers

};
} // namespace soot
