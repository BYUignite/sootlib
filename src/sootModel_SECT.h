#pragma once

#include "sootModel.h"
#include "sootDefs.h"
#include "state.h"

namespace soot {

class sootModel_SECT : public sootModel {

    //////////////// DATA MEMBERS /////////////////////

    double         binGrowthFactor;       // F^0, F^1, F^2, ... (set F here, F=2, say)
    std::vector<double> mBins; 

    //////////////// MEMBER FUNCTIONS /////////////////

    void set_mBins(const int cMin_);

public:

    virtual void getSourceTerms(state &state, 
                                std::vector<double> &sootSources,
                                std::vector<double> &gasSources,
                                std::vector<double> &pahSources) const;

    //////////////// CONSTRUCTOR FUNCTIONS ////////////

    sootModel_SECT(size_t            nsoot_,
                   nucleationModel  *nucl_,
                   growthModel      *grow_,
                   oxidationModel   *oxid_,
                   coagulationModel *coag_, 
                   double            binGrowthFactor_=2.0,
                   int               cMin_=100);

    sootModel_SECT(size_t           nsoot_,
                   nucleationMech   Nmech,
                   growthMech       Gmech,
                   oxidationMech    Omech,
                   coagulationMech  Cmech,
                   double           binGrowthFactor_=2.0,
                   int              cMin_=100);

    virtual ~sootModel_SECT() {};

};
} // namespace soot
