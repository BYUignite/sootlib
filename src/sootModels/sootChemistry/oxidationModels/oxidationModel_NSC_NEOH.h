#pragma once

#include "sootModels/sootChemistry/oxidationModels/oxidationModel.h"
#include "state.h"

namespace soot {

////////////////////////////////////////////////////////////////////////////////
/*! Oxidation by NSC + Neoh
 *
 *      Rates from Nagle and Strickland-Constable (1961) and Neoh (1981) "Soot
 *      oxidation in flames" in Particulate Carbon Formation During Combustion
 *      book
 *      C + 0.5 O2 --> CO
 *      C + OH     --> CO + H
 *
 *      Returns chemical soot oxidation rate in kg/m2*s.
 *
 */
class oxidationModel_NSC_NEOH : public oxidationModel {

//////////////// DATA MEMBERS /////////////////////

public:

//////////////// MEMBER FUNCTIONS /////////////////

public:

     double getOxidationSootRate(const state &state) const override;

//////////////// CONSTRUCTOR FUNCTIONS ////////////

public:

     oxidationModel_NSC_NEOH();
    ~oxidationModel_NSC_NEOH() override = default;
};
} // namespace soot
