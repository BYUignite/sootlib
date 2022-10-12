#pragma once

#include "state.h"
#include "sootDefs.h"

namespace soot {

class oxidationModel {

//////////////// DATA MEMBERS /////////////////////

public:

    std::map<gasSp, double>   oxidationRxnRatios;

    oxidationMech mechType;

//////////////// MEMBER FUNCTIONS /////////////////

    virtual double getOxidationSootRate(const state &state) const = 0;

    sourceTermStruct getOxidationGasRates(const state& state, const double &X1) const;

//        virtual void getOxidationPahRates(state& state) const = 0;

//////////////// CONSTRUCTOR FUNCTIONS ////////////

    oxidationModel();
    virtual ~oxidationModel() = default;
};
} // namespace soot
