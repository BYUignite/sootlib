#ifndef NUCLEATIONMODEL_LL_H
#define NUCLEATIONMODEL_LL_H

#include "nucleationModel.h"

namespace soot {

    ////////////////////////////////////////////////////////////////////////////////
    /*! Nucleation by Leung_Lindstedt (1991)
     *
     *      Rate from Leung & Lindstedt (1991), Comb. & Flame 87:289-305.
     *      Returns chemical nucleation rate in #/m3*s.
     *
     *      C2H2 --> C(s) + H2
     */
    class nucleationModel_LL : public nucleationModel {

    //////////////// DATA MEMBERS /////////////////////

    public:

        std::map<gasSp, double>  *nucleationRxnRatios;

    //////////////// MEMBER FUNCTIONS /////////////////

    public:

        double getNucleationSootRate(state& state, const std::vector<double> &mi, const std::vector<double> &wi) const override;

    //////////////// CONSTRUCTOR FUNCTIONS ////////////

    public:

        nucleationModel_LL();
        ~nucleationModel_LL() override = default;

    };
}

#endif //NUCLEATIONMODEL_LL_H
