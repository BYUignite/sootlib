#pragma once

#include "growthModels/growthModel.h"
#include "state.h"
namespace soot {

/////////////////////////////////////////////////////////////////
///
/// Moss-Brookes (1999) growth model 
///
/////////////////////////////////////////////////////////////////

class growthModel_MB : public growthModel {

///////////////// DATA MEMBERS ///////////////////// 

private:

///////////////// MEMBER FUNCTIONS ///////////////// 

public:

    double getGrowthSootRate(const state &state) const override;

///////////////// CONSTRUCTOR FUNCTIONS //////////// 

    growthModel_MB();
    ~growthModel_MB() override = default;

};
} // namespace soot
