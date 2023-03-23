#pragma once

#include "nucleationModels/nucleationModel.h"
#include "state.h"

namespace soot {

//////////////////////////////////////////////////////////////////////////////////
///
/// Lindstedt nucleation model
///
//////////////////////////////////////////////////////////////////////////////////

class nucleationModel_LINA1 : public nucleationModel {

//////////////// DATA MEMBERS /////////////////////

private:

//////////////// MEMBER FUNCTIONS /////////////////

public:

    double getNucleationSootRate(state &state) override;

    //////////////// CONSTRUCTOR FUNCTIONS ////////////

    nucleationModel_LINA1();
    ~nucleationModel_LINA1() override = default;
};
} // namespace soot
