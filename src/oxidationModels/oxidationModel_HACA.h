#pragma once

#include "oxidationModels/oxidationModel.h"
#include "state.h"

namespace soot {

//////////////////////////////////////////////////////////////////////////////////
/*! Oxidation by HACA
 *
 *      See Appel, Bockhorn, & Frenklach (2000), Comb. & Flame 121:122-136.
 *      For details, see Franklach and Wang (1990), 23rd Symposium, pp. 1559-1566.
 *
 *      Parameters for steric factor alpha updated to those given in Balthasar
 *      and Franklach (2005) Comb. & Flame 140:130-145.
 *
 *      Returns the chemical soot oxidation rate in kg/m2*s.
 *
 *      @param MomentState&     /input      local moment state; need M0 and M1
 *      @param rSoot            /output     soot growth rate (kg/m2*s)
 */
class oxidationModel_HACA : public oxidationModel {

//////////////// DATA MEMBERS /////////////////////

public:

//////////////// MEMBER FUNCTIONS /////////////////

public:

     double getOxidationSootRate(const state &state) const override;

//////////////// CONSTRUCTOR FUNCTIONS ////////////

public:

    oxidationModel_HACA();
    ~oxidationModel_HACA() override = default;
};
} // namespace soot
