#ifndef GROWTHMODEL_NONE_H
#define GROWTHMODEL_NONE_H

#include "growthModel.h"

namespace soot {

    class growthModel_NONE : public growthModel {

    //////////////// DATA MEMBERS /////////////////////

    private:

        std::map<gasSp, double>   *growthRxnRatios{};

    //////////////// MEMBER FUNCTIONS /////////////////

    public:

         double getGrowthSootRate(const state &state) const override { return 0; }

    //////////////// CONSTRUCTOR FUNCTIONS ////////////

    public:

         growthModel_NONE() = default;
        ~growthModel_NONE() override = default;

    };
}

#endif //GROWTHMODEL_NONE_H
