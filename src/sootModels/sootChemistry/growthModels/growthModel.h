#ifndef GROWTHMODEL_H
#define GROWTHMODEL_H

#include "src/state.h"
#include "src/sootModel.h"
#include "src/constants.h"

namespace soot {

    class growthModel {

    //////////////// DATA MEMBERS /////////////////////

    public:

        std::map<gasSp, double>   *growthRxnRatios;

    //////////////// MEMBER FUNCTIONS /////////////////

    public:

        virtual double getGrowthSootRate(const state& state) const = 0;

        sourceTermStruct getGrowthGasRates(const state &state, const double &G1) const;

//        virtual void getGrowthPahRates(state& state) const = 0;

    //////////////// CONSTRUCTOR FUNCTIONS ////////////

    public:

        growthModel();
        virtual ~growthModel() = default;
    };
}

#endif //GROWTHMODEL_H
