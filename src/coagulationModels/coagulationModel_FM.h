#pragma once

#include "coagulationModels/coagulationModel.h"
#include "state.h"

namespace soot {

////////////////////////////////////////////////////////////////////////////////
/*! Coagulation: Free Molecular Regime
 *
 *      Implementation of coagulationModel interface
 *
 *      Returns the value of the collision rate function (beta, or K12) (=) m3/#*s.

 *      From Seinfeld and Pandis Atmospheric Chemistry book (2016), pg. 548, chp 13.
 *
 *      @param MomentState&     \input      local moment state; need M0 and M1
 *      @param m1               \input      first particle size (kg)
 *      @param m2               \input      second particle size (kg)
 *
 */
class coagulationModel_FM : public coagulationModel {

//////////////// DATA MEMBERS /////////////////////

//////////////// MEMBER FUNCTIONS /////////////////

public:
    /**
     * Calculates coagulation rate - required by coagulationModel
     *
     * @param state
     * @param m1
     * @param m2
     * @return
     */
     double getCoagulationSootRate(const state& state, double m1, double m2) const override;

//////////////// CONSTRUCTOR FUNCTIONS ////////////

    coagulationModel_FM() { 
        FM_multiplier = 1.0;
        mechType = coagulationMech::FM; 
    }
    ~coagulationModel_FM() override = default;
};
} // namespace soot
