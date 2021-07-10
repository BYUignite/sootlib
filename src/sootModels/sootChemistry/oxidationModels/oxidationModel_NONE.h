#ifndef OXIDATIONMODEL_NONE_H
#define OXIDATIONMODEL_NONE_H

#include "oxidationModel.h"

namespace soot {

    class oxidationModel_NONE : public oxidationModel {

    //////////////// DATA MEMBERS /////////////////////

    private:

        std::map<gasSp, double>   *oxidationRxnRatios{};

    //////////////// MEMBER FUNCTIONS /////////////////

    public:

         double getOxidationSootRate(const state &state) const override { return 0; }

    //////////////// CONSTRUCTOR FUNCTIONS ////////////

    public:

         oxidationModel_NONE() = default;
        ~oxidationModel_NONE() override = default;
    };
}

#endif //OXIDATIONMODEL_NONE_H
