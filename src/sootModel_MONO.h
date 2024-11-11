#pragma once

#include "sootModel.h"
#include "sootDefs.h"
#include "state.h"

namespace soot {

///////////////////////////////////////////////////////////////////////////////
///
/// Monodispersed model (MONO)
///
///////////////////////////////////////////////////////////////////////////////

class sootModel_MONO : public sootModel {

    //////////////// DATA MEMBERS /////////////////////

    //////////////// MEMBER FUNCTIONS /////////////////

public:

    virtual void setSourceTerms(state &state);
    virtual double pahSootCollisionRatePerDimer(const state &state, const double mDimer) {return 0;}

    //////////////// CONSTRUCTOR FUNCTIONS ////////////

    sootModel_MONO(size_t            nsoot_,
                   size_t            Ntar_,
                   nucleationModel  *nucl_,
                   growthModel      *grow_,
                   oxidationModel   *oxid_,
                   coagulationModel *coag_,
                   tarModel         *tar_);

    sootModel_MONO(size_t           nsoot_,
                   size_t           Ntar_,
                   nucleationMech   Nmech,
                   growthMech       Gmech,
                   oxidationMech    Omech,
                   coagulationMech  Cmech,
                   tarMech          Tmech);

    virtual ~sootModel_MONO() {};

};
} // namespace soot
