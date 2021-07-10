#ifndef OXIDATIONMODEL_LL_H
#define OXIDATIONMODEL_LL_H

#include "oxidationModel.h"

namespace soot {

    ////////////////////////////////////////////////////////////////////////////////
    /*! Oxidation by Leung_Lindstedt (1991)
     *
     *      Rate from Leung & Lindstedt (1991), Comb. & Flame 87:289-305.
     *      Returns chemical soot oxidation rate in kg/m2*s.
     *
     *      C + 0.5 O2 --> CO
     */
    class oxidationModel_LL : public oxidationModel {

    //////////////// DATA MEMBERS /////////////////////

    public:

        std::map<gasSp, double>  *oxidationRxnRatios;

    //////////////// MEMBER FUNCTIONS /////////////////

    public:

         double getOxidationSootRate(const state &state) const override;

    //////////////// CONSTRUCTOR FUNCTIONS ////////////

    public:

         oxidationModel_LL();
        ~oxidationModel_LL() override = default;

    };
}

#endif //OXIDATIONMODEL_LL_H
