#pragma once

#include "nucleationModels/nucleationModel.h"
#include "state.h"

namespace soot {

//////////////////////////////////////////////////////////////////////////////////
///
/// Fairweather nucleation model
///
//////////////////////////////////////////////////////////////////////////////////

class nucleationModel_FAIR : public nucleationModel {

//////////////// DATA MEMBERS /////////////////////

private:

//////////////// MEMBER FUNCTIONS /////////////////

public:

    double getNucleationSootRate(state &state) override;

    //////////////// CONSTRUCTOR FUNCTIONS ////////////

    nucleationModel_FAIR();
    ~nucleationModel_FAIR() override = default;
};
} // namespace soot
