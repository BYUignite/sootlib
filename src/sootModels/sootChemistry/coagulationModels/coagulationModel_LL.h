#pragma once

#include "coagulationModel.h"

namespace soot {

////////////////////////////////////////////////////////////////////////////////
/*! Coagulation by Leung_Lindstedt
 *
 *      Implementation of coagulationModel interface
 *
 *      Returns the value of the collision rate function beta in m3/#*s.
 *
 *      Note: this assumes the free molecular regime.
 *      The original LL model is for monodispersed and has the form
 *         2*Ca*sqrt(dp)*sqrt(6*kb*T/rhoSoot)
 *         This is Eq. (4) in LL but LL is missing the 1/2 power on (6*kb*T/rhoSoot)
 *
 *      @param MomentState&     \input      local moment state; need M0 and M1
 *      @param m1               \input      first particle size (kg)
 *      @param m2               \input      second particle size (kg)
 *
 */
class coagulationModel_LL : public coagulationModel {

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

public:

    coagulationModel_LL() = default;
    ~coagulationModel_LL() override = default;
};
} // namespace soot
