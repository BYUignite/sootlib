#pragma once

#include "sootModels/sootChemistry/oxidationModels/oxidationModel.h"
#include "state.h"

namespace soot {

class oxidationModel_NONE : public oxidationModel {

//////////////// DATA MEMBERS /////////////////////

private:

//////////////// MEMBER FUNCTIONS /////////////////

public:

     double getOxidationSootRate(const state &state) const override { return 0; }

//////////////// CONSTRUCTOR FUNCTIONS ////////////

public:

     oxidationModel_NONE() : oxidationModel() {};
    ~oxidationModel_NONE() override = default;
};
} // namespace soot