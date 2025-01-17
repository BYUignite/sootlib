#pragma once

#include "oxidationModel.h"
#include "state.h"

namespace soot {

////////////////////////////////////////////////////////////////////////////////
///
/// Oxidation: no model
///
////////////////////////////////////////////////////////////////////////////////

class oxidationModel_NONE : public oxidationModel {

//////////////// DATA MEMBERS /////////////////////

private:

//////////////// MEMBER FUNCTIONS /////////////////

public:

     double getOxidationSootRate(const state &state) const override { return 0; }

//////////////// CONSTRUCTOR FUNCTIONS ////////////

public:

     oxidationModel_NONE() : oxidationModel() {
        oxidationRxnRatios[(int)gasSp::C]  = 1;      // to avoid NAN in case of oxidationMech::NONE
        mechType = oxidationMech::NONE;
     };
    ~oxidationModel_NONE() override = default;
};
} // namespace soot
