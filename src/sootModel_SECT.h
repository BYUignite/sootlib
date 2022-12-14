#pragma once

#include "sootModel.h"
#include "sootDefs.h"
#include "state.h"

namespace soot {

///////////////////////////////////////////////////////////////////////////////
///
/// Sectional model (SECT)
///
///////////////////////////////////////////////////////////////////////////////

class sootModel_SECT : public sootModel {

    //////////////// DATA MEMBERS /////////////////////

    double              binGrowthFactor;    ///< F^0, F^1, F^2, ... (set F here, F=2, say)
    std::vector<double> beta_DSi;           ///< store beta_dimer_soot_i for PAH nuc to avoid double computing

    //////////////// MEMBER FUNCTIONS /////////////////

    void set_mBins(const int cMin_);

public:

    virtual void getSourceTerms(state &state);

    virtual double pahSootCollisionRatePerDimer(const state &state, const double mDimer);

    virtual double get_M0_sectional(const state &state);
    virtual double get_M1_sectional(const state &state);

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
