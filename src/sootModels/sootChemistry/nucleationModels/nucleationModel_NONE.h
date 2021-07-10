#ifndef NUCLEATIONMODEL_NONE_H
#define NUCLEATIONMODEL_NONE_H

#include "nucleationModel.h"

namespace soot {

    class nucleationModel_NONE : public nucleationModel {

    //////////////// DATA MEMBERS /////////////////////

    private:

        std::map<gasSp, double>   *nucleationRxnRatios{};

    //////////////// MEMBER FUNCTIONS /////////////////

    public:

         double getNucleationSootRate(state& state, const std::vector<double> &mi, const std::vector<double> &wi) const override { return 0; };

    //////////////// CONSTRUCTOR FUNCTIONS ////////////

    public:

         nucleationModel_NONE() = default;
        ~nucleationModel_NONE() override = default;

    };

}

#endif //NUCLEATIONMODEL_NONE_H
