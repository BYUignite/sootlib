#pragma once

#include "sootModels/sootChemistry/nucleationModels/nucleationModel.h"
#include "state.h"

namespace soot {

class nucleationModel_NONE : public nucleationModel {

//////////////// DATA MEMBERS /////////////////////

private:

//////////////// MEMBER FUNCTIONS /////////////////

public:

     double getNucleationSootRate(state &state) override { return 0; };

//////////////// CONSTRUCTOR FUNCTIONS ////////////

     nucleationModel_NONE() : nucleationModel() {};
    ~nucleationModel_NONE() override = default;

};
} // namespace soot
