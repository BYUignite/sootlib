#pragma once

#include "sootModels/sootChemistry/nucleationModels/nucleationModel.h"
#include "state.h"

namespace soot {

////////////////////////////////////////////////////////////////////////////////
/*! Nucleation by Lindstedt (2005)
 *
 *      Rate from Lindstedt (2005), Proc. Comb. Inst. 30:775
 *      Returns chemical nucleation rate in #/m3*s.
 *
 *      C2H2 --> 2C(s) + H2
 */
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
