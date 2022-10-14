#include "sootModels/psdModels/psdModel_MONO.h"

using namespace std;
using namespace soot;

////////////////////////////////////////////////////////////////////////////////

psdModel_MONO::psdModel_MONO(sourceTermStruct* sourceTerms, int nsoot_, 
                             nucleationMech N, 
                             growthMech G, 
                             oxidationMech X, 
                             coagulationMech C)
             : psdModel(sourceTerms, nsoot_, N, G, X, C) {

    if (nsoot_ != 2)
        cerr << "Invalid number of soot moments requested. "
                "MONO model will use default value of 2 soot moments." << endl;

    nsoot = 2;
    sourceTerms->sootSourceTerms.resize(nsoot, 0);

    mechType = psdMech::MONO;
}

////////////////////////////////////////////////////////////////////////////////

void psdModel_MONO::setSourceTerms(state& state, sourceTermStruct *sourceTerms) const {

    //---------- get moments

    double M0 = state.sootVar[0];
    double M1 = state.sootVar[1];

    //---------- set weights and abscissas

    if (M0 > 0) {
        state.wts[0] = M0;
        state.absc[0] = M1 / M0;
    }

    //---------- get chemical rates

    double jNuc = nuc->getNucleationSootRate(state);
    double kGrw = grw->getGrowthSootRate(state);
    double kOxi = oxi->getOxidationSootRate(state);
    double coag = coa->getCoagulationSootRate(state, state.absc[0], state.absc[0]);

    //---------- nucleation terms

    double N0 = 0;
    double N1 = 0;

    N0 = jNuc;
    N1 = jNuc * state.cMin * gasSpMW[(int)gasSp::C] / Na;

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

    sourceTerms->sootSourceTerms[0] = (N0 + Cnd0 + G0 + X0 + C0);      // #/m3*s
    sourceTerms->sootSourceTerms[1] = (N1 + Cnd1 + G1 + X1 + C1);      // kg/m3*s

    //---------- get gas source terms

    // dummy variables
    map<gasSp, double> nucGasSrc = {{gasSp::C2H2,0},
                                    {gasSp::O,   0},
                                    {gasSp::O2,  0},
                                    {gasSp::H,   0},
                                    {gasSp::H2,  0},
                                    {gasSp::OH,  0},
                                    {gasSp::H2O, 0},
                                    {gasSp::CO,  0},
                                    {gasSp::C,   0},
                                    {gasSp::C6H6,0}};

    map<gasSp, double> grwGasSrc= {{gasSp::C2H2,0},
                                   {gasSp::O,   0},
                                   {gasSp::O2,  0},
                                   {gasSp::H,   0},
                                   {gasSp::H2,  0},
                                   {gasSp::OH,  0},
                                   {gasSp::H2O, 0},
                                   {gasSp::CO,  0},
                                   {gasSp::C,   0},
                                   {gasSp::C6H6,0}};

    map<gasSp, double> oxiGasSrc= {{gasSp::C2H2,0},
                                   {gasSp::O,   0},
                                   {gasSp::O2,  0},
                                   {gasSp::H,   0},
                                   {gasSp::H2,  0},
                                   {gasSp::OH,  0},
                                   {gasSp::H2O, 0},
                                   {gasSp::CO,  0},
                                   {gasSp::C,   0},
                                   {gasSp::C6H6,0}};

    // coagulation does not contribute to gas sources/sinks

    for (auto const& x : sourceTerms->gasSourceTerms) {
        gasSp sp = x.first;
        if (sp != gasSp::C) {
            nucGasSrc[sp] = nuc->getNucleationGasRates(state, N1).gasSourceTerms[sp];
            grwGasSrc[sp] = grw->getGrowthGasRates(state, G1).gasSourceTerms[sp];
            oxiGasSrc[sp] = oxi->getOxidationGasRates(state, X1).gasSourceTerms[sp];
            sourceTerms->gasSourceTerms[sp] = nucGasSrc[sp] + grwGasSrc[sp] + oxiGasSrc[sp];
        }
    }

    //---------- get PAH source terms

    if(nuc->mechType == nucleationMech::PAH)
        for (int sp=0; sp<(int)pahSp::size; sp++)
            sourceTerms->pahSourceTerms[sp] = nuc->getNucleationPahRates(state).pahSourceTerms[sp];
}
