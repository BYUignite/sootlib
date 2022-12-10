#pragma once

#include "oxidationModels/oxidationModel.h"
#include "state.h"

namespace soot {

//////////////////////////////////////////////////////////////////////////////////
///
/// HACA growth model (consistent with HACA growth)
///
//////////////////////////////////////////////////////////////////////////////////

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
