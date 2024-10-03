#include "sootModel_MONO.h"

using namespace std;
using namespace soot;

////////////////////////////////////////////////////////////////////////////////
///
/// Constructor taking pointers to chemistry models as input.
/// User creates these pointers nominally by "new-ing" them.
///
/// @param nsoot_ \input number of soot moments (2).
/// @param nucl_  \input pointer to nucleation model.
/// @param grow_  \input pointer to growth model.
/// @param oxid_  \input pointer to oxidation model.
/// @param coag_  \input pointer to coagulation model.
/// @param tar_   \input pointer to tar model.
///
////////////////////////////////////////////////////////////////////////////////

sootModel_MONO::sootModel_MONO(size_t            nsoot_,
                               size_t            Ntar_,
                               nucleationModel  *nucl_,
                               growthModel      *grow_,
                               oxidationModel   *oxid_,
                               coagulationModel *coag_,
                               tarModel         *tar_) :
        sootModel(nsoot_, Ntar_, nucl_, grow_, oxid_, coag_, tar_) {

    if (nsoot_ != 2)
        throw runtime_error("MONO requires nsoot=2");

    psdMechType = psdMech::MONO;
}
////////////////////////////////////////////////////////////////////////////////
///
/// Constructor taking enumerations names as input.
/// Chemistry pointers are created (new-ed) here based on those enumerations.
///
/// @param nsoot_ \input number of soot moments (2).
/// @param Nmech  \input one of enum class nucleationMech in sootDefs.h
/// @param Gmech  \input one of enum class growthMech in sootDefs.h
/// @param Omech  \input one of enum class oxidationMech in sootDefs.h
/// @param Cmech  \input one of enum class coagulationMech in sootDefs.h
/// @param Tmech  \input one of enum class tarMech in sootDefs.h
///
////////////////////////////////////////////////////////////////////////////////

sootModel_MONO::sootModel_MONO(size_t          nsoot_,
                               size_t          Ntar_,
                               nucleationMech  Nmech,
                               growthMech      Gmech,
                               oxidationMech   Omech,
                               coagulationMech Cmech,
                               tarMech         Tmech) :
        sootModel(nsoot_, Ntar_, Nmech, Gmech, Omech, Cmech, Tmech) {

    if (nsoot_ != 2)
        throw runtime_error("MONO requires nsoot=2");

    psdMechType = psdMech::MONO;
}

////////////////////////////////////////////////////////////////////////////////
///
/// Primary user interface.
/// 
/// @param state       \input  gas and soot state, set by user.
///
/// sets sources.sootSources vector
/// sets sources.gasSources vector
/// sets sources.pahSources vector
///
////////////////////////////////////////////////////////////////////////////////

void sootModel_MONO::setSourceTerms(state &state) {

    cout << "Made it to start of setSourceTerms" << endl;  // debug jansenpb

    //---------- get moments

    double M0    = state.sootVar[0];
    double M1    = state.sootVar[1];
    double Ntar0 = state.tarVar[0];

    cout << "Defined M0, M1, Ntar0" << M0 << endl;  // debug jansenpb
    //---------- set weights and abscissas

    if (M0 > 0) {
        state.wts[0] = M0;
        state.absc[0] = M1 / M0;
    }

    //---------- get chemical rates

    double jNuc = nucl->getNucleationSootRate(state);        // #/m3*s
    double kGrw = grow->getGrowthSootRate(state);
    double kOxi = oxid->getOxidationSootRate(state);
    double coa  = coag->getCoagulationSootRate(state, state.absc[0], state.absc[0]);

    cout << "Got chemical rates" << endl;  // debug jansenpb
    //---------- nucleation terms

    double N0 = 0;
    double N1 = 0;

    if (nucl->mechType != nucleationMech::NONE) {
        N0 = jNuc;                                              // #/m3*s
        N1 = jNuc * state.cMin * gasSpMW[(int)gasSp::C] / Na;   // kg_soot/m3*s (as carbon)
    }

    //---------- PAH condensation terms

    double Cnd0 = 0;
    double Cnd1 = 0;

    if (nucl->mechType == nucleationMech::PAH)
        Cnd1 = coag->getCoagulationSootRate(state, nucl->DIMER.mDimer, state.absc[0]) * 
               state.wts[0] * nucl->DIMER.nDimer * nucl->DIMER.mDimer;

    //---------- growth terms

    double G0 = 0;
    double G1 = 0;

    double Am2m3 = M0 > 0 ? M_PI*pow(6./(M_PI*rhoSoot)*M1/M0, twothird)*M0 : 0;

    if (grow->mechType != growthMech::NONE)
        G1 = kGrw * Am2m3;

    //---------- oxidation terms

    double X0 = 0;
    double X1 = 0;

    if (oxid->mechType != oxidationMech::NONE)
        X1 = -kOxi * Am2m3;

    //---------- coagulation terms

    double C0 = 0;
    double C1 = 0;

    if (coag->mechType != coagulationMech::NONE)
        C0 = -0.5*coa*state.wts[0]*state.wts[0];

    //---------- tar terms

    double T0 = 0;                               // tar equation 1 #/m3*s 
    double T1 = 0;                               // tar terms in soot mass equation kg_soot/m3*s


    if (tar->mechType != tarMech::NONE) {
        
        double incp   = tar->getInceptionTarRate(state);
        double crack  = tar->getCrackingTarRate(state);
        double gasify = tar->getSurfaceTarRate(state);
        double depo   = tar->getDepositionTarRate(state);
        

        T0 = incp - depo - crack + 2508 * Ntar0 * (G1 - X1 - gasify);
        T1 = state.mtar * depo + Am2m3 * (G1 - X1 - gasify);

        // combine to make soot source terms 

        sources.sootSources[0] = N0 + C0;
        sources.sootSources[1] = 2*state.mtar*N1 + T1;

        // combine to make tar source term 

        sources.tarSources[0]  = T0 - 2*N0;

        // set gas source terms

        vector<double> nucl_gasSources((size_t)gasSp::size, 0.0);
        vector<double> grow_gasSources((size_t)gasSp::size, 0.0);
        vector<double> oxid_gasSources((size_t)gasSp::size, 0.0);

        nucl->getNucleationGasRates(N1, nucl_gasSources);
        grow->getGrowthGasRates(    G1, grow_gasSources);
        oxid->getOxidationGasRates( X1, oxid_gasSources);

        for (size_t sp=0; sp<(size_t)gasSp::size; sp++)
            sources.gasSources[sp] = nucl_gasSources[sp] + grow_gasSources[sp] + oxid_gasSources[sp];

        //---------- set PAH source terms

        if(nucl->mechType == nucleationMech::PAH)
            sources.pahSources = nucl->nucleationPahRxnRates;        // includes both nucleation and condensation

    }


    if (tar->mechType == tarMech::NONE) {                        // jansenpb TODO: else statement?
        //---------- combine to make soot source terms

        sources.sootSources[0] = N0 + Cnd0 + G0 + X0 + C0;      // #/m3*s
        sources.sootSources[1] = N1 + Cnd1 + G1 + X1 + C1;      // kg/m3*s

        //---------- set gas source terms

        vector<double> nucl_gasSources((size_t)gasSp::size, 0.0);
        vector<double> grow_gasSources((size_t)gasSp::size, 0.0);
        vector<double> oxid_gasSources((size_t)gasSp::size, 0.0);

        nucl->getNucleationGasRates(N1, nucl_gasSources);
        grow->getGrowthGasRates(    G1, grow_gasSources);
        oxid->getOxidationGasRates( X1, oxid_gasSources);

        for (size_t sp=0; sp<(size_t)gasSp::size; sp++)
            sources.gasSources[sp] = nucl_gasSources[sp] + grow_gasSources[sp] + oxid_gasSources[sp];

        //---------- set PAH source terms

        if(nucl->mechType == nucleationMech::PAH)
            sources.pahSources = nucl->nucleationPahRxnRates;        // includes both nucleation and condensation
    }
}
