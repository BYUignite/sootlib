#pragma once

#include "nucleationModels/nucleationModel.h"
#include "state.h"

namespace soot {

//////////////////////////////////////////////////////////////////////////////////
///
/// Alex Josephson's soot nucleation model using tar molecules
///
//////////////////////////////////////////////////////////////////////////////////

class nucleationModel_AJ_RED : public nucleationModel {

//////////////// DATA MEMBERS /////////////////////

public:

//////////////// MEMBER FUNCTIONS /////////////////

    double getNucleationSootRate(state &state) override;

//////////////// CONSTRUCTOR FUNCTIONS ////////////

    nucleationModel_AJ_RED();
    ~nucleationModel_AJ_RED() override = default;

};
} // namespace soot
