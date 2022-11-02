#pragma once

#include "state.h"
#include "sootDefs.h"

#include <vector>

namespace soot {
class sootModel;

class growthModel {

//////////////// DATA MEMBERS /////////////////////

public:

    std::vector<double> growthRxnRatios;

    growthMech mechType;

    sootModel *SM;

//////////////// MEMBER FUNCTIONS /////////////////

    virtual double getGrowthSootRate(const state& state) const = 0;

    void getGrowthGasRates(const state &state, 
                           const double &msootDotGrow, 
                           std::vector<double> &gasSourcesGrow) const;

//        virtual void getGrowthPahRates(state& state) const = 0;

//////////////// CONSTRUCTOR FUNCTIONS ////////////

    growthModel() : growthRxnRatios(std::vector<double>((size_t)gasSp::size, 0.0)) { }
    virtual ~growthModel() = default;
};
} // namespace soot
