#pragma once

#include "sootModels/sootChemistry/coagulationModels/coagulationModel.h"
#include "state.h"

namespace soot {

////////////////////////////////////////////////////////////////////////////////
/*! Coagulation as harmonic mean between FM and continuum regimes. 
 *  Advocated by Frenklach.
 *
 *      Implementation of coagulationModel interface
 *      FM and Continuum as outlined in Seinfeld and Pandis 3rd Ed. pages 372, 547, 548
 *      See also Frenklach (2002) "Reaction mechanism of soot formation in flames"
 *      Phys. Chem. Chem. Phys. 4 p 2028–2037.
 *
 *      Returns the value of the collision rate function beta in m3/#*s. 
 *
 *      @param MomentState&     \input      local moment state; need M0 and M1
 *      @param m1               \input      first particle size (kg)
 *      @param m2               \input      second particle size (kg)
 *
 */
class coagulationModel_HM : public coagulationModel {

//////////////// DATA MEMBERS /////////////////////

//////////////// MEMBER FUNCTIONS /////////////////

public:
    /**
     * Calculates coagulation rate - required by coagulationModel
     *
     * @param state
     * @param m1
     * @param m2
     * @return
     */
     double getCoagulationSootRate(const state& state, double m1, double m2) const override;

//////////////// CONSTRUCTOR FUNCTIONS ////////////

     coagulationModel_HM() {
        mechType = coagulationMech::HM;
    }
    ~coagulationModel_HM() override = default;
};
} // namespace soot
