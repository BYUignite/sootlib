#pragma once

#include "coagulationModels/coagulationModel.h"
#include "state.h"

namespace soot {

////////////////////////////////////////////////////////////////////////////////
///
/// Coagulation: harmonic mean between free molecular and continuum.
///
////////////////////////////////////////////////////////////////////////////////

class coagulationModel_HM : public coagulationModel {

//////////////// DATA MEMBERS /////////////////////

//////////////// MEMBER FUNCTIONS /////////////////

public:

     double getCoagulationSootRate(const state& state, double m1, double m2) const override;

//////////////// CONSTRUCTOR FUNCTIONS ////////////

    coagulationModel_HM() { 
        FM_multiplier = 1.0;
        mechType = coagulationMech::HM; 
    }
    ~coagulationModel_HM() override = default;
};
} // namespace soot
