#pragma once

#include "sootModel.h"
#include "sootDefs.h"
#include "state.h"

namespace soot {

///////////////////////////////////////////////////////////////////////////////
///
/// Hybrid Method of Moments (HMOM) model.
///
///////////////////////////////////////////////////////////////////////////////

class sootModel_HMOM : public sootModel {

//////////////// DATA MEMBERS /////////////////////

private:
    size_t Nmom;              ///< number of soot moments (equal to nsoot - 1)

    std::vector<double> Mp6_L;  ///< arrays holding fractional moments of the large mode M_{p/6, L} where p is positive (Continuum)
    std::vector<double> Mq6_L;  ///< arrays holding fractional moments of the large mode M_{q/6, L} where q is negative (FM)
    std::vector<size_t> np;     ///< # of Mp6 entries needed based on Nmom; np[Nmom]
    std::vector<size_t> nq;     ///< # of Mq6 entries needed based on Nmom; nq[Nmom]

    std::vector<std::vector<double> > diffTable_L;     ///< set in set_diffTable_L, used in Mr_L

    // Powers of nucleated particle mass m0
    double m0_26, m0_n26, m0_n46;
    double m0_n36, m0_n16, m0_16, m0_36, m0_56, m0_76, m0_96, m0_116, m0_136, m0_156, m0_176, m0_196;

//////////////// MEMBER FUNCTIONS /////////////////

public:

    virtual void setSourceTerms(state &state);

    virtual double pahSootCollisionRatePerDimer(const state &state, const double mDimer);

private:

    void                set_diffTable_L(const std::vector<double> &M_L);
    double              Mr_L(const double r);
    void                set_fractional_moments_Mp6_Mq6_L();
    void                set_m0Powers(double mNuc);

    double              g_grid_L(int y);
    double              f_grid_L(int x, int y);
    double              get_Ik(int k, const state &state, double m0);
    std::vector<double> HMOMCoagulationRates_LL(const state &state, const std::vector<double> &M_L);

//////////////// CONSTRUCTOR FUNCTIONS ////////////

public:

    sootModel_HMOM(size_t            nsoot_,
                   nucleationModel  *nucl_,
                   growthModel      *grow_,
                   oxidationModel   *oxid_,
                   coagulationModel *coag_,
                   size_t            Ntar_ = 0,
                   tarModel         *tar_  = new tarModel_NONE);

    sootModel_HMOM(size_t           nsoot_,
                   nucleationMech   Nmech,
                   growthMech       Gmech,
                   oxidationMech    Omech,
                   coagulationMech  Cmech,
                   size_t            Ntar_ = 0,
                   tarMech          Tmech = tarMech::NONE);

    virtual ~sootModel_HMOM() {};

};
} // namespace soot
