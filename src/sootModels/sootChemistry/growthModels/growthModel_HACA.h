#ifndef GROWTHMODEL_HACA_H
#define GROWTHMODEL_HACA_H

#include "growthModel.h"

namespace soot {

    //////////////////////////////////////////////////////////////////////////////////
    /*! Growth by HACA
     *
     *      See Appel, Bockhorn, & Frenklach (2000), Comb. & Flame 121:122-136.
     *      For details, see Franklach and Wang (1990), 23rd Symposium, pp. 1559-1566.
     *
     *      Parameters for steric factor alpha updated to those given in Balthasar
     *      and Franklach (2005) Comb. & Flame 140:130-145.
     *
     *      Returns the chemical soot growth rate in kg/m2*s.
     *
     *      @param MomentState&     /input      local moment state; need M0 and M1
     *      @param rSoot            /output     soot growth rate (kg/m2*s)
     */
    class growthModel_HACA : public growthModel {

    //////////////// DATA MEMBERS /////////////////////

    public:

        std::map<gasSp, double>   *growthRxnRatios;

    //////////////// MEMBER FUNCTIONS ////////////////

    public:

        double getGrowthSootRate(const state& state) const override;

    //////////////// CONSTRUCTOR FUNCTIONS ////////////

    public:

        growthModel_HACA();
        ~growthModel_HACA() override = default;
    };
}

#endif //GROWTHMODEL_HACA_H
