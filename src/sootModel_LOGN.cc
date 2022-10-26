#include "sootModels/psdModels/psdModel_LOGN.h"

using namespace std;
using namespace soot;

////////////////////////////////////////////////////////////////////////////////

psdModel_LOGN::psdModel_LOGN(int nsoot_, 
                             nucleationMech N, 
                             growthMech G, 
                             oxidationMech X, 
                             coagulationMech C) : psdModel(nsoot_, N, G, X, C) {

    // warn user if wrong number of soot moments is requested
    if (nsoot_ != 3)
        cerr << "Invalid number of soot moments requested. "
                "LOGN model will use default value of 3 soot moments." << endl;

    // specify number of soot moments for LOGN model
    nsoot = 3;

    mechType = psdMech::LOGN;
}

////////////////////////////////////////////////////////////////////////////////

void psdModel_LOGN::setSourceTerms(state& state, sourceTermStruct *sourceTerms) const {

    double N0 = 0, N1 = 0, N2 = 0;
    double G0 = 0, G1 = 0, G2 = 0;
    double X0 = 0, X1 = 0, X2 = 0;
    double C0 = 0, C1 = 0, C2 = 0;
    double Cnd0 = 0, Cnd1 = 0, Cnd2 = 0;

    // get moment values
    const double M0 = state.sootVar[0];
    const double M1 = state.sootVar[1];
    const double M2 = state.sootVar[2];

    // calculate coagulation constants
    const double Kfm = eps_c * sqrt(M_PI * kb * state.T / 2) * pow(6 / M_PI / rhoSoot, 2 / 3.0);
    const double Kc = 2 * kb * state.T / (3 / state.muGas);
    const double Kcp = 2 * 1.657 * state.getGasMeanFreePath() * pow(M_PI / 6 * rhoSoot, 1.0 / 3);

    // reused Mk function results here
    const double M13 =  Mk( 1.0 / 3, M0, M1, M2);
    const double M23 =  Mk( 2.0 / 3, M0, M1, M2);
    const double Mn12 = Mk(-1.0 / 2, M0, M1, M2);
    const double Mn16 = Mk(-1.0 / 6, M0, M1, M2);
    const double Mn13 = Mk(-1.0 / 3, M0, M1, M2);
    const double Mn23 = Mk(-2.0 / 3, M0, M1, M2);
    const double M43 =  Mk( 4.0 / 3, M0, M1, M2);
    const double M53 =  Mk( 5.0 / 3, M0, M1, M2);
    const double M12 =  Mk( 1.0 / 2, M0, M1, M2);
    const double M56 =  Mk( 5.0 / 6, M0, M1, M2);
    const double M76 =  Mk( 7.0 / 6, M0, M1, M2);
    const double M16 =  Mk( 1.0 / 6, M0, M1, M2);

    //---------- nucleation terms

    double Jnuc = nuc->getNucleationSootRate(state);    // #/m3*s

    // PAH nucleation and condensation; getNucleationSootRate function call above still required to set DIMER variables
    if (nuc->mechType == nucleationMech::PAH) {

        double mDimer = nuc->DIMER.mDimer;
        double nDimer = nuc->DIMER.nDimer;

        // PAH nucleation
        const double Ifm = Kfm * bCoag * (M0 *   pow(mDimer,  1.0 / 6)  + 2 * M13 *  pow(mDimer, -1.0 / 6) +
                                          M23 *  pow(mDimer, -1.0 / 2)  + 2 * Mn16 * pow(mDimer,  1.0 / 3) +
                                          Mn12 * pow(mDimer,  2.0 / 3)  + 2 * Mn16 * pow(mDimer,  1.0 / 3) + M16);

        const double Ic = Kc * (2 * M0 + Mn13 * pow(mDimer, 1.0 / 3) + M13 * pow(mDimer, -1.0 / 3) +
                                Kcp * (M0 * pow(mDimer, -1.0 / 3) + Mn13 + M13 * pow(mDimer, -2.0 / 3) +
                                       Mn23 * pow(mDimer, 1.0 / 3)));

        const double beta_DD = coa->getCoagulationSootRate(state, mDimer, mDimer);

        Jnuc = 0.5 * beta_DD * nDimer * nDimer;

        // PAH condensation
        const double Ifm1 = Ifm;
        const double Ifm2 = Kfm * bCoag * (M1      * pow(mDimer,  1.0 / 6) + 2 * M43 * pow(mDimer, -1.0 / 6) +
                                           M53     * pow(mDimer, -1.0 / 2) +     M12 * pow(mDimer,  2.0 / 3) +
                                           2 * M56 * pow(mDimer,  1.0 / 3) +     M76);

        const double Ic1 = Ic;
        const double Ic2 = Kc * (2 * M1 + M23 * pow(mDimer, 1.0 / 3) + M43 * pow(mDimer, -1.0 / 3) +
                                 Kcp * (M1  * pow(mDimer, -1.0 / 3) + M23 + M43 * pow(mDimer, -2.0 / 3) + M13 * pow(mDimer, 1.0 / 3)));

        Cnd1 = mDimer * nDimer * (Ic1 * Ifm1) / (Ic1 + Ifm1);
        Cnd2 = 2 * mDimer * nDimer * (Ic2 * Ifm2) / (Ic2 + Ifm2);

    } // end PAH nucleation/condensation block

    const double mMin = state.cMin * gasSpMW[(int)gasSp::C] / Na;

    N0 = Jnuc;                 // #/m3*s
    N1 = Jnuc * mMin;          // kg_soot/m3*s
    N2 = Jnuc * mMin * mMin;

    //---------- growth terms

    double Kgrw = grw->getGrowthSootRate(state);

    G0 = 0;
    G1 = Kgrw * M_PI * pow(6 / rhoSoot / M_PI, 2.0 / 3) * M23;
    G2 = Kgrw * M_PI * pow(6 / rhoSoot / M_PI, 2.0 / 3) * M53;

    //---------- oxidation terms

    double Koxi = oxi->getOxidationSootRate(state);

    X0 = 0;
    X1 = Koxi * M_PI * pow(6.0 / rhoSoot / M_PI, 2.0 / 3) * M23;
    X2 = Koxi * M_PI * pow(6.0 / rhoSoot / M_PI, 2.0 / 3) * M53 * 2;

    //---------- coagulation terms

    // free molecular regime
    double C0_fm = -Kfm * bCoag * (M0 * M16 + 2 * M13 * Mn16 + M23 * Mn12);
    double C2_fm = 2 * Kfm * bCoag * (M1 * M76 + 2 * M43 * M56 + M53 * M12);

    // continuum regime
    double C0_c = -Kc * (M0 * M0 + M13 * Mn13 + Kcp * (M0 * Mn13 + M13 * Mn23));
    double C2_c = 2 * Kc * (M1 * M1 + M23 * M43 + Kcp * (M1 * M23 + M13 * M43));

    // harmonic mean
    C0 = C0_fm * C0_c / (C0_fm + C0_c);
    C1 = 0;
    C2 = C2_fm * C2_c / (C2_fm + C2_c);

    //---------- combine to make soot source terms

    sourceTerms->sootSourceTerms[0] = (N0 + G0 + Cnd0 - X0 + C0);
	sourceTerms->sootSourceTerms[1] = (N1 + G1 + Cnd1 - X1 + C1);
	sourceTerms->sootSourceTerms[2] = (N2 + G2 + Cnd2 - X2 + C2);

	//---------- set gas source terms

    for (int sp=0; sp<(int)gasSp::size; sp++) {
        if(sp == (int)gasSp::C) continue;
	        sourceTerms->gasSourceTerms[sp] = nuc->getNucleationGasRates(state, N1).gasSourceTerms[sp] +
	                                          grw->getGrowthGasRates(    state, G1).gasSourceTerms[sp] +
	                                          oxi->getOxidationGasRates( state, X1).gasSourceTerms[sp];
	}

    //---------- get PAH source terms

    if(nuc->mechType == nucleationMech::PAH)
        for (int sp=0; sp<(int)pahSp::size; sp++)
            sourceTerms->pahSourceTerms[sp] = nuc->getNucleationPahRates(state).pahSourceTerms[sp];

}

////////////////////////////////////////////////////////////////////////////////

double psdModel_LOGN::Mk(double k, double M0, double M1, double M2) {

    double M0_exp = 1 + 0.5 * k * (k - 3);
    double M1_exp = k * (2 - k);
    double M2_exp = 0.5 * k * (k - 1);

    if (M2 == 0 && M2_exp < 0)
        M2_exp = 0;

    return pow(M0, M0_exp) * pow(M1, M1_exp) * pow(M2, M2_exp);
}
