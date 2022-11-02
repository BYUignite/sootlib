#pragma once

#include "state.h"

namespace soot {

class sootModel;

/**
 * Interface used to calculate coagulation rate given a state and two masses
 */
class coagulationModel {

    //////////////// DATA MEMBERS /////////////////////

public:

    sootModel *SM;

protected:

    double FM_multiplier;         // multiply the FM rate by this constant (1.0 default, user set)

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

    void set_FM_multiplier(double FM_multiplier_) {
        FM_multiplier = FM_multiplier_;
    }

    coagulationMech mechType;

    //////////////// CONSTRUCTOR FUNCTIONS ////////////

    coagulationModel() = default;
    virtual ~coagulationModel() = default;      // Virtual deconstructor since interface will be used in the form of pointers

};
} // namespace soot
