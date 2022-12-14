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

    virtual double getKfm(const state& state) const {
        throw std::runtime_error("ERROR: coagulationModel::getKfm should not be called, but child coagulationModel_FM::getKfm is fine");
        return -1.0;}

    virtual double getKc(const state& state) const {
        throw std::runtime_error("ERROR: coagulationModel::getKc should not be called, but child coagulationModel_CONTINUUM::getKc is fine");
        return -1.0;}

    virtual double getKcp(const state& state) const {
        throw std::runtime_error("ERROR: coagulationModel::getKcp should not be called, but child coagulationModel_CONTINUUM::getKcp is fine");
        return -1.0;}

    void set_FM_multiplier(double FM_multiplier_) {
        FM_multiplier = FM_multiplier_;
    }

    //////////////// CONSTRUCTOR FUNCTIONS ////////////

    coagulationModel() = default;
    virtual ~coagulationModel() = default;      // Virtual deconstructor since interface will be used in the form of pointers

};
} // namespace soot
