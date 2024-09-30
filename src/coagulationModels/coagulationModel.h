#pragma once

#include "state.h"

namespace soot {

class sootModel;

///////////////////////////////////////////////////////////////////////////////
///
/// Abstract base class to calculate coagulation rate given a state and two masses.
///
///////////////////////////////////////////////////////////////////////////////

class coagulationModel {

    //////////////// DATA MEMBERS /////////////////////

public:

    sootModel *SM;                ///< back pointer to soot model
    coagulationMech mechType;     ///< identity of the type of coagulation (child)

protected:

    double FM_multiplier;         ///< multiply the FM rate by this (1.0 default, user set); make =9/2/eps_c for LL

    //////////////// MEMBER FUNCTIONS /////////////////

public:

    virtual double getCoagulationSootRate(const state& state, double m1, double m2) const = 0;

    double getKfm(const state& state) const {
        return FM_multiplier * eps_c * sqrt(0.5*M_PI*kb*state.T)*pow(6./(M_PI*rhoSoot), twothird);
    }

    double getKc(const state& state) const {
        return 2.*kb*state.T/(3./state.muGas);
    }

    double getKcp(const state& state) const {
        return 2.*1.657*state.getGasMeanFreePath()*pow(M_PI*rhoSoot/6., onethird);
    }

    void set_FM_multiplier(double FM_multiplier_) {
        FM_multiplier = FM_multiplier_;
    }

    //////////////// CONSTRUCTOR FUNCTIONS ////////////

    coagulationModel() = default;
    virtual ~coagulationModel() = default;      // Virtual deconstructor since interface will be used in the form of pointers

};
} // namespace soot
