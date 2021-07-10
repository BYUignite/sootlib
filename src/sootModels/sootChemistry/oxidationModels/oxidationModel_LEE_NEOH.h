#ifndef OXIDATIONMODEL_LEE_NEOH_H
#define OXIDATIONMODEL_LEE_NEOH_H

#include "oxidationModel.h"

namespace soot {

    ////////////////////////////////////////////////////////////////////////////////
    /*! Oxidation by Lee et al. + Neoh
     *
     *      Rates from Lee et al. (1962) Comb. & Flame 6:137-145 and Neoh (1981)
     *      "Soot oxidation in flames" in Particulate Carbon Formation During
     *      Combustion book
     *      C + 0.5 O2 --> CO
     *      C + OH     --> CO + H
     *
     *      Returns chemical soot oxidation rate in kg/m2*s.
     *
     *      @param MomentState&     /input      local moment state; need M0 and M1
     *      @param rSoot            /output     soot growth rate (kg/m2*s)
     */
    class oxidationModel_LEE_NEOH : public oxidationModel {

    //////////////// DATA MEMBERS /////////////////////

    public:

        std::map<gasSp, double>  *oxidationRxnRatios;

    //////////////// MEMBER FUNCTIONS /////////////////

    public:

         double getOxidationSootRate(const state &state) const override;

    //////////////// CONSTRUCTOR FUNCTIONS ////////////

    public:

         oxidationModel_LEE_NEOH();
        ~oxidationModel_LEE_NEOH() override = default;
    };
}

#endif //OXIDATIONMODEL_LEE_NEOH_H
