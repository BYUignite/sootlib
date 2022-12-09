#pragma once

#include "state.h"
#include "sootDefs.h"

#include <vector>

namespace soot {

class sootModel;

///////////////////////////////////////////////////////////////////////////////
///
/// Abstract base class to calculate nucleation rates
///
///////////////////////////////////////////////////////////////////////////////

class nucleationModel {

    //////////////// DATA MEMBERS /////////////////////

public:

    sootModel *SM;                              ///< back pointer to soot model
    coagulationMech mechType;                   ///< identity of the type of coagulation (child)

    dimerStruct DIMER = dimerStruct();          ///< used for PAH nucleation only

    std::vector<double> nucleationRxnRatios;    ///< mole ratios for gas species rate coupling
    std::vector<double> nucleationPahRxnRates;  ///< mole ratios for PAH gas species rate coupling

    //////////////// MEMBER FUNCTIONS /////////////////

    virtual double getNucleationSootRate(state &state) = 0;

    void getNucleationGasRates(const state &state, 
                               const double &msootDotNucl, 
                               std::vector<double> &gasSourcesNucl) const;

    //////////////// CONSTRUCTOR FUNCTIONS ////////////

    nucleationModel() : nucleationPahRxnRates(std::vector<double>((int)pahSp::size, 0.0)),
                        nucleationRxnRatios(  std::vector<double>((int)gasSp::size, 0.0)) { }
    virtual ~nucleationModel() = default;

};
} // namespace soot
