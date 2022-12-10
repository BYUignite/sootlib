#pragma once

#include "nucleationModels/nucleationModel.h"
#include "state.h"

namespace soot {

////////////////////////////////////////////////////////////////////////////////
///
/// Nucleation: no model
///
////////////////////////////////////////////////////////////////////////////////

class nucleationModel_NONE : public nucleationModel {

    //////////////// DATA MEMBERS /////////////////////

private:

    //////////////// MEMBER FUNCTIONS /////////////////

public:

    double getNucleationSootRate(state &state) override { return 0; };

    //////////////// CONSTRUCTOR FUNCTIONS ////////////

    nucleationModel_NONE() : nucleationModel() {
        mechType = soot::nucleationMech::NONE;
    };
    ~nucleationModel_NONE() override = default;

};
} // namespace soot
