#pragma once

#include "state.h"
#include "constants.h"

namespace soot {

class growthModel {

//////////////// DATA MEMBERS /////////////////////

public:

    std::map<gasSp, double>   growthRxnRatios;

//////////////// MEMBER FUNCTIONS /////////////////

    virtual double getGrowthSootRate(const state& state) const = 0;

    sourceTermStruct getGrowthGasRates(const state &state, const double &G1) const;

//        virtual void getGrowthPahRates(state& state) const = 0;

//////////////// CONSTRUCTOR FUNCTIONS ////////////

    growthModel();
    virtual ~growthModel() = default;
};
} // namespace soot
