#pragma once

#include "coagulationModels/coagulationModel.h"
#include "state.h"

namespace soot {

////////////////////////////////////////////////////////////////////////////////
///
/// Coagulation: Model by Fuchs that transitions between the FM and C regimes.
///
////////////////////////////////////////////////////////////////////////////////

class coagulationModel_FUCHS : public coagulationModel {

    //////////////// DATA MEMBERS /////////////////////

    //////////////// MEMBER FUNCTIONS /////////////////

public:

    double getCoagulationSootRate(const state& state, double m1, double m2) const override;

    //////////////// CONSTRUCTOR FUNCTIONS ////////////

    coagulationModel_FUCHS() { 
        FM_multiplier = 1.0;
        mechType = coagulationMech::FUCHS; 
    }
    ~coagulationModel_FUCHS() override = default;
};
} // namespace soot
