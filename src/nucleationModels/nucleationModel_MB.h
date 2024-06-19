#pragma once

#include "nucleationModels/nucleationModel.h"
#include "state.h"

namespace soot {

    /////////////////////////////////////////////////////////////////
    ///
    /// Moss-Brookes nucleation model 
    /// 
    /////////////////////////////////////////////////////////////////

class nucleationModel_MB : public nucleationModel {

////////////////// DATA MEMBERS //////////////////// 

public:

////////////////// MEMBER FUNCTIONS //////////////// 

public:

    double getNucleationSootRate(state &state) override;

    ////////////// CONSTRUCTOR FUNCTIONS ///////////////

    nucleationModel_MB();
    ~nucleationModel_MB() override = default;
};
} // namespace soot
