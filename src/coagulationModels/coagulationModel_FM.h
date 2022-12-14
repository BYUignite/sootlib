#pragma once

#include "coagulationModels/coagulationModel.h"
#include "state.h"

namespace soot {

////////////////////////////////////////////////////////////////////////////////
///
/// Coagulation: Continuum Regime
///
////////////////////////////////////////////////////////////////////////////////

class coagulationModel_FM : virtual public coagulationModel {

    //////////////// DATA MEMBERS /////////////////////

    //////////////// MEMBER FUNCTIONS /////////////////

public:

     double getCoagulationSootRate(const state& state, double m1, double m2) const override;

     double getKfm(const state& state) const override {
         return FM_multiplier * eps_c * sqrt(0.5*M_PI*kb*state.T)*pow(6./(M_PI/rhoSoot), twothird);
     }

    //////////////// CONSTRUCTOR FUNCTIONS ////////////

    coagulationModel_FM() { 
        FM_multiplier = 1.0;
        mechType = coagulationMech::FM; 
    }
    ~coagulationModel_FM() override = default;
};
} // namespace soot
