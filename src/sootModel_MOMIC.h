#pragma once

#include "sootModel.h"
#include "sootDefs.h"
#include "state.h"

namespace soot {

///////////////////////////////////////////////////////////////////////////////
///
/// Method of Moments with Interpolative Closure (MOMIC) model.
///
///////////////////////////////////////////////////////////////////////////////

class sootModel_MOMIC : public sootModel {

//////////////// DATA MEMBERS /////////////////////

private:
    size_t Nmom;              ///< number of soot moments (may decrese from downselectIfNeeded)

    std::vector<double> Mp6;  ///< arrays holding fractional moments M_{p/6} where p is posiitive (Continuum)
    std::vector<double> Mq6;  ///< arrays holding fractional moments M_{q/6} where q is negative  (FM)
    std::vector<size_t> np;   ///< \# of Mp6 entries needed based on Nmom; if Nmom=3, then np[3] is # Mp6 entries to fill
    std::vector<size_t> nq;   ///< \# of Mq6 entries needed based on Nmom; if Nmom=3, then nq[3] is # Mq6 entries to fill

    std::vector<std::vector<double> > diffTable;     ///< set in set_diffTable, used in Mr

    double mDn46,                                    ///< mDimer^{-4/6}, etc.; for continuum 
           mDn26, mD26;
    double mDn36,                                    ///< mDimer^{-3/6}, etc.; for free molecular
           mDn16, mD16,  mD36,  mD56,  mD76,
           mD96,  mD116, mD136, mD156, mD176, mD196;

//////////////// MEMBER FUNCTIONS /////////////////

public:

    virtual void setSourceTerms(state &state);

    virtual double pahSootCollisionRatePerDimer(const state &state, const double mDimer);

private:

    void                downselectIfNeeded(std::vector<double> &M);
    double              f_grid(int x, int y);
    double              g_grid(int y);
    std::vector<double> MOMICCoagulationRates(const state& state, std::vector<double>& M);
    double              Mr(const double r);                              // fractional moments using polynomial interp among log M
    void                set_diffTable(const std::vector<double> &l10M);  // needed by Mr
    void                set_fractional_moments_Mp6_Mq6();
    void                set_mDimerPowers();

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
