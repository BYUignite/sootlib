#pragma once

#include "tarModels/tarModel.h"
#include "state.h"


namespace soot {

///////////////////////////////////////////////////////////////////////////////
///
/// Alexander Brown Revised Soot Model
///
///////////////////////////////////////////////////////////////////////////////

class tarModel_BROWN : public tarModel {
    
////////////////// DATA MEMBERS: //////////////////////////////////////////
    
private:

////////////////// MEMBER FUNCTIONS ////////////////////////////////////////

public:

    double getCrackingTarRate(state &state) override;
    double getSurfaceTarRate(state &state) override;
    double getDepositionTarRate(state &state) override {return 0;};

///////////////// CONSTRUCTOR ///////////////////////////////////////////// 

    tarModel_BROWN() {
        mechType = tarMech::BROWN;
    }
    ~tarModel_BROWN() override = default;
    
};
} // namespace soot

