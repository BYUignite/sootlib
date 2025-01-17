#pragma once

#include "oxidationModel.h"
#include "state.h"

namespace soot {

///////////////////////////////////////////////////////////////////////////
///
/// Oxidation by Brown and Fletcher 1998 (revised by Josephson and Lignell 2016)
///
///////////////////////////////////////////////////////////////////////////

class oxidationModel_BROWN : public oxidationModel {

/////////////////// DATA MEMBERS ///////////////////////////// 

public: 

/////////////////// MEMBER FUNCTIONS ///////////////////////// 

public:

    double getOxidationSootRate(const state &state) const override;

/////////////////// CONSTRUCTOR FUNCTIONS //////////////////// 

public:

    oxidationModel_BROWN();
    ~oxidationModel_BROWN() override = default;

};
} // namespace soot 
