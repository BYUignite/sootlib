#pragma once

#include "oxidationModel.h"
#include "state.h"

namespace soot {

//////////////////////////////////////////////////////////////////////////////////
///
/// Oxidation by Leung, Lindstedt, and Jones (1991)
///
//////////////////////////////////////////////////////////////////////////////////

class oxidationModel_LL : public oxidationModel {

//////////////// DATA MEMBERS /////////////////////

public:

//////////////// MEMBER FUNCTIONS /////////////////

public:

     double getOxidationSootRate(const state &state) const override;

//////////////// CONSTRUCTOR FUNCTIONS ////////////

public:

     oxidationModel_LL();
    ~oxidationModel_LL() override = default;

};
} // namespace soot
