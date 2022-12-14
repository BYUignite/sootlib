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

    double getKc(const state& state) const override  { 
        return 2.*kb*state.T/(3./state.muGas);
    }
    double getKcp(const state& state) const override { 
        return 2.*1.657*state.getGasMeanFreePath()*pow(M_PI*rhoSoot/6., onethird);
    }

    //////////////// CONSTRUCTOR FUNCTIONS ////////////

    coagulationModel_CONTINUUM() { 
        FM_multiplier = 1.0;
        mechType = coagulationMech::CONTINUUM; 
    }
    ~coagulationModel_CONTINUUM() override = default;
};
} // namespace soot
