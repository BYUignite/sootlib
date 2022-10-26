#pragma once

#include "state.h"
#include "sootDefs.h"

#include <vector>

namespace soot {

class nucleationModel {

//////////////// DATA MEMBERS /////////////////////

public:

    dimerStruct DIMER = dimerStruct();      // used for PAH nucleation only

    std::vector<double> nucleationRxnRatios;
    std::vector<double> nucleationPahRxnRates;

    nucleationMech mechType;

//////////////// MEMBER FUNCTIONS /////////////////

    virtual double getNucleationSootRate(state &state) = 0;

    void getNucleationGasRates(const state &state, 
                               const double &msootDotNucl, 
                               std::vector<double> gasSourcesNucl) const;

//////////////// CONSTRUCTOR FUNCTIONS ////////////

    nucleationModel() : nucleationPahRxnRates(std::vector<double>((int)pahSp::size, 0.0)),
                        nucleationRxnRatios(  std::vector<double>((int)gasSp::size, 0.0)) { }
    virtual ~nucleationModel() = default;

};
} // namespace soot
