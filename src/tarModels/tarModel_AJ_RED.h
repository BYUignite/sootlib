#pragma once

#include "tarModels/tarModel.h"
#include "state.h"

namespace soot {

//////////////////////////////////////////////////////////////////////////////////
///
/// Alex Josephson reduced tar model
///
//////////////////////////////////////////////////////////////////////////////////

class tarModel_AJ_RED : public tarModel {

//////////////// DATA MEMBERS /////////////////////

public:

//////////////// MEMBER FUNCTIONS /////////////////

    double getInceptionTarRate(state &state) override;
    double getCrackingTarRate(state &state) override;
    double getDepositionTarRate(state &state) override;
    double getSurfaceTarRate(state &state) override;

//////////////// CONSTRUCTOR FUNCTIONS ////////////

    tarModel_AJ_RED();
    ~tarModel_AJ_RED() override = default;

};
} // namespace soot
