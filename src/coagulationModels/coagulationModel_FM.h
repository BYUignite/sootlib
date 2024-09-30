#pragma once

#include "coagulationModels/coagulationModel.h"
#include "state.h"

namespace soot {

////////////////////////////////////////////////////////////////////////////////
///
/// Coagulation: Free Molecular Regime
///
////////////////////////////////////////////////////////////////////////////////

class coagulationModel_FM : virtual public coagulationModel {

    //////////////// DATA MEMBERS /////////////////////

    //////////////// MEMBER FUNCTIONS /////////////////

public:

    double getCoagulationSootRate(const state& state, double m1, double m2) const override;

    //////////////// CONSTRUCTOR FUNCTIONS ////////////

    coagulationModel_FM() { 
        FM_multiplier = 1.0;
        mechType = coagulationMech::FM; 
    }
    ~coagulationModel_FM() override = default;

};
} // namespace soot
