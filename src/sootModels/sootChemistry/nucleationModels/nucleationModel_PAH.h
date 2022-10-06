#pragma once

#include "sootModels/sootChemistry/nucleationModels/nucleationModel.h"
#include "state.h"

namespace soot {

////////////////////////////////////////////////////////////////////////////////
/*! PAH nucleation by Blanquart et al. (2009)
 *
 *      Rate from Blanquart & Pitsch (2009) article "A joint
 *      volume-surface-hydrogen multi-variate model for soot formation," ch. 27
 *      in Combustion Generated Fine Carbonaceous Particles ed. Bockhorn et al.
 *      Returns chemical nucleation rate in #/m3*s.
 *
 */
class nucleationModel_PAH : public nucleationModel {

//////////////// DATA MEMBERS /////////////////////

public:

//////////////// MEMBER FUNCTIONS /////////////////

    double getNucleationSootRate(state &state) override;
//        void getNucleationPahRates(state &state) override;

//////////////// CONSTRUCTOR FUNCTIONS ////////////

     nucleationModel_PAH();
    ~nucleationModel_PAH() override = default;
};
} // namespace soot
