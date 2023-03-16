#pragma once

#include "oxidationModels/oxidationModel.h"
#include "state.h"

namespace soot {

//////////////////////////////////////////////////////////////////////////////////
///
/// Josephson et al. optimized O2 & OH oxidation model
///
//////////////////////////////////////////////////////////////////////////////////

class oxidationModel_OPTJ : public oxidationModel {

//////////////// DATA MEMBERS /////////////////////

public:

//////////////// MEMBER FUNCTIONS /////////////////

public:

     double getOxidationSootRate(const state &state) const override;

//////////////// CONSTRUCTOR FUNCTIONS ////////////

public:

     oxidationModel_OPTJ();
    ~oxidationModel_OPTJ() override = default;
};
} // namespace soot
