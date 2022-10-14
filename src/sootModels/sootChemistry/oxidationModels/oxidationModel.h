#pragma once

#include "state.h"
#include "sootDefs.h"

#include <vector>

namespace soot {

class oxidationModel {

//////////////// DATA MEMBERS /////////////////////

public:

    std::vector<double> oxidationRxnRatios;

    oxidationMech mechType;

//////////////// MEMBER FUNCTIONS /////////////////

    virtual double getOxidationSootRate(const state &state) const = 0;

    sourceTermStruct getOxidationGasRates(const state& state, const double &X1) const;

//        virtual void getOxidationPahRates(state& state) const = 0;

//////////////// CONSTRUCTOR FUNCTIONS ////////////

    oxidationModel() : oxidationRxnRatios(std::vector<double>((int)gasSp::size, 0.0)) {
        oxidationRxnRatios[(int)gasSp::C] = 1.0;
    }
    virtual ~oxidationModel() = default;
};
} // namespace soot
