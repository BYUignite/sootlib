#pragma once

#include "state.h"
#include "sootDefs.h"

#include <vector>

namespace soot {

class sootModel;

///////////////////////////////////////////////////////////////////////////////
///
/// Abstract base class to calculate oxidation rates
///
///////////////////////////////////////////////////////////////////////////////

class oxidationModel {

    //////////////// DATA MEMBERS /////////////////////

public:

    sootModel *SM;                           ///< back pointer to soot model
    coagulationMech mechType;                ///< identity of the type of coagulation (child)

    std::vector<double> oxidationRxnRatios;  ///< mole ratios for gas species rate coupling

    //////////////// MEMBER FUNCTIONS /////////////////

    virtual double getOxidationSootRate(const state &state) const = 0;

    void getOxidationGasRates(const state &stt, 
                               const double &msootDotOxid, 
                               std::vector<double> &gasSourcesOxid) const;

    //////////////// CONSTRUCTOR FUNCTIONS ////////////

    oxidationModel() : oxidationRxnRatios(std::vector<double>((int)gasSp::size, 0.0)) {
        oxidationRxnRatios[(int)gasSp::C] = 1.0;
    }
    virtual ~oxidationModel() = default;
};
} // namespace soot
