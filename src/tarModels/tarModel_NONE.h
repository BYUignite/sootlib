
#pragma once

#include "tarModels/tarModel.h"
#include "state.h"

namespace soot {

////////////////////////////////////////////////////////////////////////////////
///
/// Tar: no model
///
////////////////////////////////////////////////////////////////////////////////

class tarModel_NONE : public tarModel {

    //////////////// DATA MEMBERS /////////////////////

private:

    //////////////// MEMBER FUNCTIONS /////////////////

public:

    double getInceptionTarRate(state &state) override { return 0; };
    double getCrackingTarRate(state &state) override { return 0; };
    double getDepositionTarRate(state &state) override { return 0; };
    double getSurfaceTarRate(state &state) override { return 0; };

    //////////////// CONSTRUCTOR FUNCTIONS ////////////

    tarModel_NONE() : tarModel() {
        mechType = soot::tarMech::NONE;
    };
    ~tarModel_NONE() override = default;

};
} // namespace soot
