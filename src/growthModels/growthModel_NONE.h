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

     growthModel_NONE() : growthModel() {
         growthRxnRatios[(int)gasSp::C] = 1.0; // to avoid NAN when using growthModel::NONE for gas sources
         mechType = growthMech::NONE;

     };
    ~growthModel_NONE() override = default;

};
} // namespace soot
