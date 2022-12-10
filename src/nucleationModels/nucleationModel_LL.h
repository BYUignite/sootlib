#pragma once

#include "nucleationModels/nucleationModel.h"
#include "state.h"

namespace soot {

//////////////////////////////////////////////////////////////////////////////////
///
/// Lindstedt nucleation model
///
//////////////////////////////////////////////////////////////////////////////////

class nucleationModel_LL : public nucleationModel {

//////////////// DATA MEMBERS /////////////////////

public:

//////////////// MEMBER FUNCTIONS /////////////////

    double getNucleationSootRate(state &state) override;

//////////////// CONSTRUCTOR FUNCTIONS ////////////

    nucleationModel_LL();
    ~nucleationModel_LL() override = default;

};
} // namespace soot
