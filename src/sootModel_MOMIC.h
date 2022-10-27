#pragma once

#include "sootModel.h"
#include "sootDefs.h"
#include "state.h"

namespace soot {

class sootModel_MOMIC : public sootModel {

//////////////// DATA MEMBERS /////////////////////


//////////////// MEMBER FUNCTIONS /////////////////

public:

    virtual void getSourceTerms(state &state, 
                                std::vector<double> &sootSources,
                                std::vector<double> &gasSources,
                                std::vector<double> &pahSources) const;
private:

    void          downselectIfNeeded(std::vector<double> &M) const;
    static double f_grid(int x, int y, const std::vector<double>& M);
    static double MOMICCoagulationRate(const state& state, size_t r, std::vector<double>& M);
    static double lagrangeInterp(double x_i, const std::vector<double>& x, const std::vector<double>& y);
    static double MOMIC(double p, const std::vector<double>& M);

//////////////// CONSTRUCTOR FUNCTIONS ////////////

public:

    sootModel_MOMIC(size_t            nsoot_,
                    nucleationModel  *nucl_,
                    growthModel      *grow_,
                    oxidationModel   *oxid_,
                    coagulationModel *coag_);

    sootModel_MOMIC(size_t           nsoot_,
                    nucleationMech   Nmech,
                    growthMech       Gmech,
                    oxidationMech    Omech,
                    coagulationMech  Cmech);

    virtual ~sootModel_MOMIC() {};

};
} // namspace soot
