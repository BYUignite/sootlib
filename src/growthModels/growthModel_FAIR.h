#pragma once

#include "growthModels/growthModel.h"
#include "state.h"

namespace soot {

//////////////////////////////////////////////////////////////////////////////////
///
/// Fairweather (1992) growth model
///
//////////////////////////////////////////////////////////////////////////////////

class growthModel_FAIR : public growthModel {

//////////////// DATA MEMBERS /////////////////////

private:

//////////////// MEMBER FUNCTIONS /////////////////

public:

     double getGrowthSootRate(const state &state) const override;

//////////////// CONSTRUCTOR FUNCTIONS ////////////

    growthModel_FAIR();
    ~growthModel_FAIR() override = default;

};
} // namespace soot
