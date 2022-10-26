#include "soot_MONO.h"

using namespace std;
using namespace soot;

////////////////////////////////////////////////////////////////////////////////

sootModel_MONO::sootModel_MONO(size_t nsoot_,
                               nucleationModel  *nucl_,
                               oxidationModel   *oxid_,
                               growthModel      *grow_,
                               coagulationModel *coag_) :
        sootModel(nsoot_, nucl_, oxid_, grow_, coag_) {

    if (nsoot_ != 2)
        cerr << "Invalid number of soot moments requested. "
                "MONO model will use default value of 2 soot moments." << endl;

    nsoot = 2;
}

////////////////////////////////////////////////////////////////////////////////

void soot::sootModel_MONO::getSourceTerms(const state &stt, 
                                          std::vector<double> &sootSources,
                                          std::vector<double> &gasSources) const {

    //---------- get moments

    double M0 = state.sootVar[0];
    double M1 = state.sootVar[1];

    //---------- set weights and abscissas

    if (M0 > 0) {
        state.wts[0] = M0;
        state.absc[0] = M1 / M0;
    }

    //---------- get chemical rates

    double jNuc = nuc->getNucleationSootRate(state);        // #/m3*s
    double kGrw = grw->getGrowthSootRate(state);
    double kOxi = oxi->getOxidationSootRate(state);
    double coag = coa->getCoagulationSootRate(state, state.absc[0], state.absc[0]);

    //---------- nucleation terms

    double N0 = 0;
    double N1 = 0;

    N0 = jNuc;                                              // #/m3*s
    N1 = jNuc * state.cMin * gasSpMW[(int)gasSp::C] / Na;   // kg_soot/m3*s (as carbon)

    //---------- PAH condensation terms

    double Cnd0 = 0;
    double Cnd1 = 0;

    if (nuc->mechType == nucleationMech::PAH) {

        double nDimer = nuc->DIMER.nDimer;
        double mDimer = nuc->DIMER.mDimer;

        Cnd1 = nDimer * mDimer * coa->getCoagulationSootRate(state, mDimer, state.absc[0]) * state.wts[0];

    }

    //---------- growth terms

    double G0 = 0;
    double G1 = 0;

    double Am2m3 = M0 > 0 ? M_PI * pow(abs(6 / (M_PI * rhoSoot) * M1 / M0), 2.0 / 3) * abs(M0) : 0;

    G1 = kGrw * Am2m3;

    //---------- oxidation terms

    double X0 = 0;
    double X1 = 0;

    X1 = -kOxi * Am2m3;

    //---------- coagulation terms

    double C0 = 0;
    double C1 = 0;

    //C0 = -0.5 * coag * state.wts[0] * state.wts[0];
    C0 = -coag * state.wts[0] * state.wts[0];

    //---------- combine to make soot source terms

    sootSources[0] = (N0 + Cnd0 + G0 + X0 + C0);      // #/m3*s
    sootSources[1] = (N1 + Cnd1 + G1 + X1 + C1);      // kg/m3*s

    //---------- set gas source terms

    vector<double> nucl_gasSources((size_t)::gasSp::size, 0.0);
    vector<double> grow_gasSources((size_t)::gasSp::size, 0.0);
    vector<double> oxid_gasSources((size_t)::gasSp::size, 0.0);

    nuc->getNucleationGasRates(state, N1, nucl_gasSources);
    nuc->getGrowthGasRates(    state, G1, grow_gasSources);
    nuc->getOxidationGasRates( state, X1, oxid_gasSources);

    for (size_t sp=0; sp<(size_t)gasSp::size; sp++)
        gasSourceTerms[sp] = nucl_gasSources[sp] + grow_gasSources[sp] + oxid_gasSources[sp];

}