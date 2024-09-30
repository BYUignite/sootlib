#pragma once

#include "coagulationModels/coagulationModel.h"
#include "state.h"

namespace soot {

////////////////////////////////////////////////////////////////////////////////
///
/// Coagulation: Continuum Regime
///
////////////////////////////////////////////////////////////////////////////////

class coagulationModel_CONTINUUM : virtual public coagulationModel {

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
