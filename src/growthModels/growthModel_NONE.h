#pragma once

#include "growthModels/growthModel.h"
#include "state.h"

namespace soot {

////////////////////////////////////////////////////////////////////////////////
///
/// Growth: no model
///
////////////////////////////////////////////////////////////////////////////////

class growthModel_NONE : public growthModel {

//////////////// DATA MEMBERS /////////////////////

private:

//////////////// MEMBER FUNCTIONS /////////////////

public:

     double getGrowthSootRate(const state &state) const override { return 0; }

//////////////// CONSTRUCTOR FUNCTIONS ////////////

     growthModel_NONE() : growthModel() {};
    ~growthModel_NONE() override = default;

};
} // namespace soot
