#pragma once

#include "sootModel.h"
#include "sootDefs.h"
#include "state.h"

namespace soot {

///////////////////////////////////////////////////////////////////////////////
///
/// Quadrature Method of Moments (QMOM) model
///
///////////////////////////////////////////////////////////////////////////////

class sootModel_QMOM : public sootModel {

//////////////// DATA MEMBERS /////////////////////

//////////////// MEMBER FUNCTIONS /////////////////

public:

    virtual void setSourceTerms(state &state);

private:

    static void   wheeler(const std::vector<double>& m, size_t N, std::vector<double>& w, std::vector<double>& x);
    static void   getWtsAbs(const std::vector<double>& M, std::vector<double>& weights, std::vector<double>& abscissas);
    static double Mr(double r, const std::vector<double>& wts, const std::vector<double>& absc);

//////////////// CONSTRUCTOR ////////////

public:

    sootModel_QMOM(size_t            nsoot_,
                   size_t            Ntar_,
                   nucleationModel  *nucl_,
                   growthModel      *grow_,
                   oxidationModel   *oxid_,
                   coagulationModel *coag_,
                   tarModel         *tar_);

    sootModel_QMOM(size_t           nsoot_,
                   size_t           Ntar_,
                   nucleationMech   Nmech,
                   growthMech       Gmech,
                   oxidationMech    Omech,
                   coagulationMech  Cmech,
                   tarMech          Tmech);

    virtual ~sootModel_QMOM() {};

};
} // namespace soot
