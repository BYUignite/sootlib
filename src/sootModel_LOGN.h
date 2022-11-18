#pragma once

#include "sootModel.h"
#include "sootDefs.h"
#include "state.h"

namespace soot {

class sootModel_LOGN : public sootModel {

    //////////////// DATA MEMBERS /////////////////////

    //////////////// MEMBER FUNCTIONS /////////////////

public:

    virtual void getSourceTerms(state &state, 
                                std::vector<double> &sootSources,
                                std::vector<double> &gasSources,
                                std::vector<double> &pahSources) const;

    double Mk(double k, double M0, double M1, double M2) const;

    virtual double pahSootCollisionRatePerDimer(const state &state, const double mDimer) const;

    //////////////// CONSTRUCTOR FUNCTIONS ////////////

    sootModel_LOGN(size_t            nsoot_,
                   nucleationModel  *nucl_,
                   growthModel      *grow_,
                   oxidationModel   *oxid_,
                   coagulationModel *coag_);

    sootModel_LOGN(size_t           nsoot_,
                   nucleationMech   Nmech,
                   growthMech       Gmech,
                   oxidationMech    Omech,
                   coagulationMech  Cmech);

    virtual ~sootModel_LOGN() {};

};
} // namspace soot
