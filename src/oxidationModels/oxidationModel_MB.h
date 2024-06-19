#pragma once

#include "oxidationModel.h"
#include "state.h"

namespace soot {

//////////////////////////////////////////////////////////////////////
///
/// Oxidation by Moss & Brookes
///
//////////////////////////////////////////////////////////////////////

class oxidationModel_MB : public oxidationModel {

////////////////// DATA MEMBERS //////////////////// 

public:

////////////////// MEMBER FUNCTIONS //////////////// 

public:

    double getOxidationSootRate(const state &state) const override;

////////////////// CONSTRUCTOR FUNCTIONS /////////// 

public:

    oxidationModel_MB();
    ~oxidationModel_MB() override = default;

};
} // namespace soot
