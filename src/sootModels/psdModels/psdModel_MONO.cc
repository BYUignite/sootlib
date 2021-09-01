#include "psdModel_MONO.h"

using namespace std;
using namespace soot;

////////////////////////////////////////////////////////////////////////////////

psdModel_MONO::psdModel_MONO(sourceTermStruct* sourceTerms, int nVar, nucleationMech N, growthMech G, oxidationMech X, coagulationMech C)
             : psdModel(sourceTerms, nVar, N, G, X, C) {

    // warn user if wrong number of soot moments is requested
    if (nVar != 2)
        cerr << "Invalid number of soot moments requested. "
                "MONO model will use default value of 2 soot moments." << endl;

    // specify number of soot moments for MONO model
    nMom = 2;

    // initialize sourceTerms soot variable
    sourceTerms->sootSourceTerms.resize(nMom, 0);

    // note nucleation mech in case PAH is needed
    nucleationMechanism = N;

}

////////////////////////////////////////////////////////////////////////////////

void psdModel_MONO::getSourceTermsImplementation(state& state, sourceTermStruct *sourceTerms) const {

    //---------- get moments

    double M0 = state.sootMom[0];
    double M1 = state.sootMom[1];

    //---------- set weights and abscissas

    if (M0 > 0) {
        state.wts.at(0) = M0;
        state.absc.at(0) = M1 / M0;
    }

    //---------- get chemical rates

    double jNuc = nuc->getNucleationSootRate(state);
    double kGrw = grw->getGrowthSootRate(state);
    double kOxi = oxi->getOxidationSootRate(state);
    double coag = coa->getCoagulationSootRate(state, state.absc.at(0), state.absc.at(0));

    //---------- nucleation terms

    double N0 = jNuc;
    double N1 = jNuc * state.cMin * gasSpMW.at(gasSp::C) / Na;

    //---------- PAH condensation terms

    double Cnd0 = 0;
    double Cnd1 = 0;

    if (nucleationMechanism == nucleationMech::PAH) {

        double nDimer = nuc->DIMER.nDimer;
        double mDimer = nuc->DIMER.mDimer;

        Cnd1 = nDimer * mDimer * coa->getCoagulationSootRate(state, mDimer, state.absc.at(0)) * state.wts.at(0);

    }

    //---------- growth terms

    double Am2m3 = M0 > 0 ? M_PI * pow(abs(6 / (M_PI * rhoSoot) * M1 / M0), 2.0 / 3) * abs(M0) : 0;

    double G0 = 0;
    double G1 = kGrw * Am2m3;

    //---------- oxidation terms

    double X0 = 0;
    double X1 = -kOxi * Am2m3;

    //---------- coagulation terms

    double C0 = -0.5 * coag * state.wts.at(0) * state.wts.at(0);
    double C1 = 0;

    //---------- combine to make soot source terms

    sourceTerms->sootSourceTerms.at(0) = (N0 + Cnd0 + G0 + X0 + C0) / state.rhoGas;
    sourceTerms->sootSourceTerms.at(1) = (N1 + Cnd1 + G1 + X1 + C1) / state.rhoGas;

    //---------- get gas source terms

    map<gasSp, double> nucGasSrc = nuc->getNucleationGasRates(state, N1).gasSourceTerms;    // condensation lumped in with nucleation //TODO check this
    map<gasSp, double> grwGasSrc = grw->getGrowthGasRates(state, G1).gasSourceTerms;
    map<gasSp, double> oxiGasSrc = oxi->getOxidationGasRates(state, X1).gasSourceTerms;
    // coagulation does not contribute to gas sources/sinks

    for (auto const& x : sourceTerms->gasSourceTerms) {
        gasSp sp = x.first;
        if (sp != gasSp::C)
            sourceTerms->gasSourceTerms.at(sp) = nucGasSrc.at(sp) + grwGasSrc.at(sp) + oxiGasSrc.at(sp);
    }

}
