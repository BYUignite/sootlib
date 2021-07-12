#ifndef NUCLEATIONMODEL_LIN_H
#define NUCLEATIONMODEL_LIN_H

#include "nucleationModel.h"

namespace soot {

    ////////////////////////////////////////////////////////////////////////////////
    /*! Nucleation by Lindstedt (2005)
     *
     *      Rate from Lindstedt (2005), Proc. Comb. Inst. 30:775
     *      Returns chemical nucleation rate in #/m3*s.
     *
     *      C2H2 --> C(s) + H2
     *      C6H6 --> 6C(s) + 3H2
     *
     *      NOTE: second reaction ignored here
     */
    class nucleationModel_LIN : public nucleationModel {

    //////////////// DATA MEMBERS /////////////////////

    private:

        std::map<gasSp, double>   *nucleationRxnRatios;

    //////////////// MEMBER FUNCTIONS /////////////////

    public:

        double getNucleationSootRate(state& state, const std::vector<double> &mi, const std::vector<double> &wi) override;

        //////////////// CONSTRUCTOR FUNCTIONS ////////////

    public:

        nucleationModel_LIN();
        ~nucleationModel_LIN() override = default;
    };
}

#endif //NUCLEATIONMODEL_LIN_H
