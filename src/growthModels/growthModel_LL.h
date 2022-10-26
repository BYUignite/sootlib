#pragma once

#include "growthModels/growthModel.h"
#include "state.h"

namespace soot {

////////////////////////////////////////////////////////////////////////////////
/*! Growth by Leung_Lindstedt (1991)
 *
 *      Rate from Leung & Lindstedt (1991), Comb. & Flame 87:289-305.
 *      Returns chemical surface growth rate in kg/m2*s.
 *
 *      C2H2 + nC(s) --> (n+2)C(s) + H2
 */
class growthModel_LL : public growthModel {

//////////////// DATA MEMBERS /////////////////////

private:

//////////////// MEMBER FUNCTIONS /////////////////

public:

     double getGrowthSootRate(const state &state) const override;

//////////////// CONSTRUCTOR FUNCTIONS ////////////

    growthModel_LL();
    ~growthModel_LL() override = default;

};
} // namespace soot
