#pragma once

#include "coagulationModels/coagulationModel.h"
#include "state.h"

namespace soot {

////////////////////////////////////////////////////////////////////////////////
/*! Coagulation by Fuchs
 *
 *      Implementation of coagulationModel interface
 *
 *      Rate comes from Seinfeld and Pandis Atmospheric Chemistry book (2016), pg. 548, chp 13
 *      (see also chapter 9). Details and clarification in Fuchs' Mechanics of Aerosols book (1964).
 *
 *      Seinfeld is missing the sqrt(2) in the final term for g. This is needed to reproduce
 *      his plot. Fuchs' book has the sqrt(2). I've seen another book
 *      (https://authors.library.caltech.edu/25069/7/AirPollution88-Ch5.pdf) with 1.0 in
 *      place of both sqrt(2) factors. This gives 5% max error in the D=D curve.
 *
 *      Returns the value of the collision rate function beta in m3/#*s.
 *
 *      @param MomentState&     \input      local moment state; need M0 and M1
 *      @param m1               \input      first particle size (kg)
 *      @param m2               \input      second particle size (kg)
 */
class coagulationModel_FUCHS : public coagulationModel {

    //////////////// DATA MEMBERS /////////////////////

    //////////////// MEMBER FUNCTIONS /////////////////

public:

    /**
     * Calculates coagulation rate - required by coagulationModel
     *
     * @param state
     * @param m1
     * @param m2
     * @return
     */
    double getCoagulationSootRate(const state& state, double m1, double m2) const override;

    //////////////// CONSTRUCTOR FUNCTIONS ////////////

    coagulationModel_FUCHS() { 
        FM_multiplier = 1.0;
        mechType = coagulationMech::FUCHS; 
    }
    ~coagulationModel_FUCHS() override = default;
};
} // namespace soot
