#pragma once

#include "sootModels/sootChemistry/coagulationModels/coagulationModel.h"
#include "state.h"

namespace soot {

/**
* The default implementation of coagulationModel interface
*/
class coagulationModel_NONE : public coagulationModel {

//////////////// DATA MEMBERS /////////////////////

private:

//////////////// MEMBER FUNCTIONS /////////////////

public:

    /**
     * Always returns 0 for coagulation rate - required by coagulationModel
     *
     * @param state
     * @param m1
     * @param m2
     */
     double getCoagulationSootRate(const state& state, double m1, double m2) const override { return 0; }

//////////////// CONSTRUCTOR FUNCTIONS ////////////

    coagulationModel_NONE() : coagulationModel() {
        mechType = coagulationMech::NONE;
    };
    ~coagulationModel_NONE() override = default;
};
} // namespace soot
