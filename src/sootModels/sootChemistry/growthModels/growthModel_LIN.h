#pragma once

#include "sootModels/sootChemistry/growthModels/growthModel.h"
#include "state.h"

namespace soot {

class growthModel_LIN : public growthModel {

//////////////// DATA MEMBERS /////////////////////

public:

//////////////// MEMBER FUNCTIONS /////////////////

public:

    ////////////////////////////////////////////////////////////////////////////////
    /*! Growth by Lindstedt (1994)
     *
     *      Rate from Bockhorn (1994) pg. 417, "Simplified Soot Nucleation and Surface Growth Steps..."
     *      Equation (27.36). Returns chemical surface growth rate in kg/m2*s. Assumes that rate is
     *      proportional to number of particles (M0) but independent of available surface area.
     *
     *      @param MomentState&     /input      local moment state; need M0 and M1
     *      @param rSoot            /output     soot growth rate (kg/m2*s)
     */
     double getGrowthSootRate(const state &state) const override;

//////////////// CONSTRUCTOR FUNCTIONS ////////////

public:

    growthModel_LIN();
    ~growthModel_LIN() override = default;

};
} // namespace soot
