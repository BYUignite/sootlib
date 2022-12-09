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

    virtual void getSourceTerms(state &state, 
                                std::vector<double> &sootSources,
                                std::vector<double> &gasSources,
                                std::vector<double> &pahSources) const;

    //////////////// CONSTRUCTOR FUNCTIONS ////////////

    sootModel_MONO(size_t            nsoot_,
                   nucleationModel  *nucl_,
                   growthModel      *grow_,
                   oxidationModel   *oxid_,
                   coagulationModel *coag_);

    sootModel_MONO(size_t           nsoot_,
                   nucleationMech   Nmech,
                   growthMech       Gmech,
                   oxidationMech    Omech,
                   coagulationMech  Cmech);

    virtual ~sootModel_MONO() {};

};
} // namespace soot
