#pragma once

#include "nucleationModels/nucleationModel.h"
#include "state.h"

namespace soot {

//////////////////////////////////////////////////////////////////////////////////
///
/// Lindstedt nucleation model
///
//////////////////////////////////////////////////////////////////////////////////

class nucleationModel_LIN : public nucleationModel {

//////////////// DATA MEMBERS /////////////////////

private:

//////////////// MEMBER FUNCTIONS /////////////////

public:

    double getNucleationSootRate(state &state) override;

    //////////////// CONSTRUCTOR FUNCTIONS ////////////

    nucleationModel_LIN();
    ~nucleationModel_LIN() override = default;
};
} // namespace soot
