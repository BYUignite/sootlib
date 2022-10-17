#pragma once

#include "state.h"
#include "sootDefs.h"
#include <vector>

namespace soot {

class growthModel {

//////////////// DATA MEMBERS /////////////////////

public:

    std::vector<double> growthRxnRatios;

    growthMech mechType;

//////////////// MEMBER FUNCTIONS /////////////////

    virtual double getGrowthSootRate(const state& state) const = 0;

    sourceTermStruct getGrowthGasRates(const state &state, const double &G1) const;

//        virtual void getGrowthPahRates(state& state) const = 0;

//////////////// CONSTRUCTOR FUNCTIONS ////////////

    growthModel() : growthRxnRatios(std::vector<double>((size_t)gasSp::size, 0.0)) {
        growthRxnRatios[(int)gasSp::C] = 1.0;
    }
    virtual ~growthModel() = default;
};
} // namespace soot
