#pragma once

#include "growthModels/growthModel.h"
#include "state.h"

namespace soot {

//////////////////////////////////////////////////////////////////////////////////
///
/// Leung_Lindstedt (1991) growth model
///
//////////////////////////////////////////////////////////////////////////////////

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
