#pragma once

#include "coagulationModels/coagulationModel.h"
#include "state.h"

namespace soot {

////////////////////////////////////////////////////////////////////////////////
///
/// Coagulation: No model
///
////////////////////////////////////////////////////////////////////////////////

class coagulationModel_NONE : public coagulationModel {

    //////////////// DATA MEMBERS /////////////////////

private:

    //////////////// MEMBER FUNCTIONS /////////////////

public:

    /////////////////////
    /// Always returns 0 for coagulation rate - required by coagulationModel
    ///
    /// @param state
    /// @param m1
    /// @param m2
    /////////////////////

     double getCoagulationSootRate(const state& state, double m1, double m2) const override { return 0; }

    //////////////// CONSTRUCTOR FUNCTIONS ////////////

    coagulationModel_NONE() { 
        FM_multiplier = 1.0;
        mechType = coagulationMech::NONE; 
    }
    ~coagulationModel_NONE() override = default;
};
} // namespace soot
