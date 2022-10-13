#pragma once

#include "state.h"
#include "sootDefs.h"

namespace soot {

class nucleationModel {

//////////////// DATA MEMBERS /////////////////////

public:

    dimerStruct DIMER = dimerStruct();      // used for PAH nucleation only

    std::map<gasSp, double>   nucleationRxnRatios;
    std::vector<double>       nucleationPahRxnRates;

    nucleationMech mechType;

//////////////// MEMBER FUNCTIONS /////////////////

    virtual double getNucleationSootRate(state &state) = 0;

    sourceTermStruct getNucleationGasRates(const state& state, const double &N1) const;

    sourceTermStruct getNucleationPahRates(const state& state) const;

//////////////// CONSTRUCTOR FUNCTIONS ////////////

    nucleationModel();
    virtual ~nucleationModel() = default;

};
} // namespace soot
