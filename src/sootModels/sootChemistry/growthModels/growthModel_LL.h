#ifndef GROWTHMODEL_LL_H
#define GROWTHMODEL_LL_H

#include "growthModel.h"

namespace soot {

    ////////////////////////////////////////////////////////////////////////////////
    /*! Growth by Leung_Lindstedt (1991)
     *
     *      Rate from Leung & Lindstedt (1991), Comb. & Flame 87:289-305.
     *      Returns chemical surface growth rate in kg/m2*s.
     *
     *      C2H2 + nC(s) --> (n+2)C(s) + H2
     */
    class growthModel_LL : public growthModel {

    //////////////// DATA MEMBERS /////////////////////

    private:

        std::map<gasSp, double>  *growthRxnRatios;

    //////////////// MEMBER FUNCTIONS /////////////////

    public:

         double getGrowthSootRate(const state &state) const override;

    //////////////// CONSTRUCTOR FUNCTIONS ////////////

    public:

        growthModel_LL();
        ~growthModel_LL() override = default;

    };
}

#endif //GROWTHMODEL_LL_H
