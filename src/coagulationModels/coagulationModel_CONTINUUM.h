#pragma once

#include "coagulationModels/coagulationModel.h"
#include "state.h"

namespace soot {

////////////////////////////////////////////////////////////////////////////////
///
/// Coagulation: Continuum Regime
/// Implementation of coagulationModel interface
///
/// From Seinfeld and Pandis Atmospheric Chemistry book (2016), pg. 547, chp 13.
///
/// @param MomentState      \input      local moment state; need M0 and M1
/// @param m1               \input      first particle size (kg)
/// @param m2               \input      second particle size (kg)
/// @return value of the collion rate function (beta12 or K12) (=) m3/\#*s
///
////////////////////////////////////////////////////////////////////////////////

class coagulationModel_CONTINUUM : public coagulationModel {

    //////////////// DATA MEMBERS /////////////////////

    //////////////// MEMBER FUNCTIONS /////////////////

public:

    double getCoagulationSootRate(const state& state, double m1, double m2) const override;

    //////////////// CONSTRUCTOR FUNCTIONS ////////////

    coagulationModel_CONTINUUM() { 
        FM_multiplier = 1.0;
        mechType = coagulationMech::CONTINUUM; 
    }
    ~coagulationModel_CONTINUUM() override = default;
};
} // namespace soot
