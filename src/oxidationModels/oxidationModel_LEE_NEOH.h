#pragma once

#include "oxidationModels/oxidationModel.h"
#include "state.h"

namespace soot {

//////////////////////////////////////////////////////////////////////////////////
///
/// Lee (O2) + Neoh (OH) Oxidation model
///
//////////////////////////////////////////////////////////////////////////////////

class oxidationModel_LEE_NEOH : public oxidationModel {

//////////////// DATA MEMBERS /////////////////////

public:

//////////////// MEMBER FUNCTIONS /////////////////

public:

     double getOxidationSootRate(const state &state) const override;

//////////////// CONSTRUCTOR FUNCTIONS ////////////

public:

     oxidationModel_LEE_NEOH();
    ~oxidationModel_LEE_NEOH() override = default;
};
} // namespace soot
