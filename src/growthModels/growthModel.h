#pragma once

#include "state.h"
#include "sootDefs.h"

#include <vector>

namespace soot {
class sootModel;

///////////////////////////////////////////////////////////////////////////////
///
/// Abstract base class to calculate growth rate
///
///////////////////////////////////////////////////////////////////////////////

class growthModel {

    //////////////// DATA MEMBERS /////////////////////

public:

    sootModel *SM;                 ///< back pointer to soot model
    growthMech mechType;           ///< identity of the type of growth (child)

    std::vector<double> growthRxnRatios;  ///< mole ratios for gas species rate coupling

    //////////////// MEMBER FUNCTIONS /////////////////

    virtual double getGrowthSootRate(const state& state) const = 0;

    void getGrowthGasRates( const double &msootDotGrow, 
                           std::vector<double> &gasSourcesGrow) const;

    //////////////// CONSTRUCTOR FUNCTIONS ////////////

    growthModel() : growthRxnRatios(std::vector<double>((size_t)gasSp::size, 0.0)) { }
    virtual ~growthModel() = default;
};
} // namespace soot
