#pragma once

#include "sootModel.h"
#include "sootDefs.h"
#include "state.h"

namespace soot {

///////////////////////////////////////////////////////////////////////////////
///
/// Lognormal distribution model (LOGN)
///
///////////////////////////////////////////////////////////////////////////////

class sootModel_LOGN : public sootModel {

    //////////////// DATA MEMBERS /////////////////////

    //////////////// MEMBER FUNCTIONS /////////////////

public:

    virtual void setSourceTerms(state &state);

    double Mr(double k, double M0, double M1, double M2) const;

    virtual double pahSootCollisionRatePerDimer(const state &state, const double mDimer) const;

    //////////////// CONSTRUCTOR FUNCTIONS ////////////

    sootModel_LOGN(size_t            nsoot_,
                   size_t            Ntar_,
                   nucleationModel  *nucl_,
                   growthModel      *grow_,
                   oxidationModel   *oxid_,
                   coagulationModel *coag_,
                   tarModel         *tar_);

    sootModel_LOGN(size_t           nsoot_,
                   size_t           Ntar_,
                   nucleationMech   Nmech,
                   growthMech       Gmech,
                   oxidationMech    Omech,
                   coagulationMech  Cmech,
                   tarMech          Tmech);

    virtual ~sootModel_LOGN() {};

};
} // namspace soot
