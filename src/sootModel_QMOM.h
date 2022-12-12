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

    virtual void getSourceTerms(state &state, 
                                std::vector<double> &sootSources,
                                std::vector<double> &gasSources,
                                std::vector<double> &pahSources) const;

private:

    static void   wheeler(const std::vector<double>& m, size_t N, std::vector<double>& w, std::vector<double>& x);
    static void   getWtsAbs(const std::vector<double>& M, std::vector<double>& weights, std::vector<double>& abscissas);
    static double Mr(double r, const std::vector<double>& wts, const std::vector<double>& absc);

//////////////// CONSTRUCTOR ////////////

public:

    sootModel_QMOM(size_t            nsoot_,
                   nucleationModel  *nucl_,
                   growthModel      *grow_,
                   oxidationModel   *oxid_,
                   coagulationModel *coag_);

    sootModel_QMOM(size_t           nsoot_,
                   nucleationMech   Nmech,
                   growthMech       Gmech,
                   oxidationMech    Omech,
                   coagulationMech  Cmech);

    virtual ~sootModel_QMOM() {};

};
} // namespace soot
