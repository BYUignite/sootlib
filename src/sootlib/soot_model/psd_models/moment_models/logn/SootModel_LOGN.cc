#include "SootModel_LOGN.h"

#include <cmath>

using namespace std;
using namespace soot;

SootModel_LOGN* SootModel_LOGN::getInstance(unique_ptr<CoagulationModel> coagulationModel,
                                            unique_ptr<GrowthModel> growthModel,
                                            unique_ptr<NucleationModel> nucleationModel,
                                            unique_ptr<OxidationModel> oxidationModel) {
    return new SootModel_LOGN(move(coagulationModel),
                              move(growthModel),
                              move(nucleationModel),
                              move(oxidationModel));
}
SootModel_LOGN::SootModel_LOGN(unique_ptr<CoagulationModel> coagulationModel,
                               unique_ptr<GrowthModel> growthModel,
                               unique_ptr<NucleationModel> nucleationModel,
                               unique_ptr<OxidationModel> oxidationModel) : SootChemistry(move(coagulationModel),
																						  move(growthModel),
																						  move(nucleationModel),
																						  move(oxidationModel)) {
}
SourceTerms SootModel_LOGN::getSourceTerms(State& state) const {
    const double M0 = state.getMoment(0);
    const double M1 = state.getMoment(0);
    const double M2 = state.getMoment(0);

    const double b_coag = 0.8536;

    double Cnd0 = 0, Cnd1 = 0, Cnd2 = 0;

    const double Kfm = getKfm(state);
    const double Kc = getKc(state);
    const double Kcp = getKcp(state);

    const double mmin = state.getCMin() * MW_C / Na;

    MassRateRatios massRateRatios;

    // reused Mk function results here
    const double temp0 = Mk(1.0 / 3, M0, M1, M2);
    const double temp1 = Mk(2.0 / 3, M0, M1, M2);
    const double temp2 = Mk(-1.0 / 2, M0, M1, M2);
    const double temp3 = Mk(-1.0 / 6, M0, M1, M2);
    const double temp4 = Mk(-1.0 / 3, M0, M1, M2);
    const double temp5 = Mk(-2.0 / 3, M0, M1, M2);
    const double temp6 = Mk(4.0 / 3, M0, M1, M2);
    const double temp7 = Mk(5.0 / 3, M0, M1, M2);
    const double temp8 = Mk(1.0 / 2, M0, M1, M2);
    const double temp9 = Mk(5.0 / 6, M0, M1, M2);
    const double temp10 = Mk(7.0 / 6, M0, M1, M2);
    const double temp11 = Mk(1.0 / 6, M0, M1, M2);

    double Jnuc;
    if (nucleationModel->getMechanism() != NucleationMechanism::PAH) {
        Jnuc = nucleationModel->getNucleationRate(state, {}, {}, massRateRatios);
    }
    else {
        const double Ifm = Kfm * b_coag * (M0 * pow(state.getMDimer(), 1.0 / 6)
        	+ 2 * temp0 * pow(state.getMDimer(), -1.0 / 6)
        	+ temp1 * pow(state.getMDimer(), -1.0 / 2)
        	+ temp2 * pow(state.getMDimer(), 2.0 / 3)
        	+ 2 * temp3 * pow(state.getMDimer(), 1.0 / 3)
        	+ temp11);
        const double Ic = Kc * (2 * M0 + temp4 * pow(state.getMDimer(), 1.0 / 3)
        	+ temp0 * pow(state.getMDimer(), -1.0 / 3)
        	+ Kcp * (M0 * pow(state.getMDimer(), -1.0 / 3)
        	+ temp4
        	+ temp0 * pow(state.getMDimer(), -2.0 / 3)
        	+ temp5 * pow(state.getMDimer(), 1.0 / 3)));

        const double beta_DD = coagulationModel->getCoagulationRate(state, state.getMDimer(), state.getMDimer());
        // TODO I'm concerned this might not be the right DIMER
        Jnuc = 0.5 * beta_DD * state.getDimer() * state.getDimer();

        const double Ifm1 = Ifm;
        const double Ifm2 = Kfm * b_coag * (M1 * pow(state.getMDimer(), 1.0 /6)
        	+ 2 * temp6 * pow(state.getMDimer(), -1.0 / 6)
        	+ temp7 * pow(state.getMDimer(), -1.0 / 2)
        	+ temp8 * pow(state.getMDimer(), 2.0 / 3)
        	+ 2 * temp9 * pow(state.getMDimer(), 1.0 / 3)
        	+ temp10);
        const double Ic1 = Ic;
        const double Ic2 = Kc * (2 * M1
            + temp1 * pow(state.getMDimer(), 1.0 / 3)
        	+ temp6 * pow(state.getMDimer(), -1.0 / 3)
        	+ Kcp * (M1 * pow(state.getMDimer(), -1.0 / 3)
        	+ temp1
        	+ temp6 * pow(state.getMDimer(), -2.0 / 3)
        	+ temp0 * pow(state.getMDimer(), 1.0 / 3)));

        Cnd1 = state.getMDimer() * state.getDimer() * (Ic1 * Ifm1) / (Ic1 + Ifm1);
        Cnd2 = 2 * state.getMDimer() * state.getDimer() * (Ic2 * Ifm2) / (Ic2 + Ifm2);
    }

    const double N0 = Jnuc, N1 = Jnuc * mmin, N2 = Jnuc * mmin * mmin;

    const double Kgrw = growthModel->getGrowthRate(state, massRateRatios);

    const double term = Kgrw * M_PI * pow(6 / state.getRhoSoot() / M_PI, 2.0 / 3);

    const double G0 = 0, G1 = term * temp1, G2 = term * temp7;

    const double Koxi = oxidationModel->getOxidationRate(state, massRateRatios);

    const double X0 = 0;
    const double X1 = Koxi * M_PI * pow(6.0 / state.getRhoSoot() / M_PI, 2.0 / 3) * temp1;
    const double X2 = Koxi * M_PI * pow(6.0 / state.getRhoSoot() / M_PI, 2.0 / 3) * temp7 * 2;

    const double C0_fm = -Kfm * b_coag * (M0 * temp11 + 2 * temp0 * temp3 + temp1 * temp2);
//    const double C1_fm = 0;
    const double C2_fm = 2 * Kfm * b_coag * (M1 * temp10 + 2 * temp6 * temp9 + temp7 * temp8);

    const double C0_c = -Kc * (M0 * M0 + temp0 * temp4 + Kcp * (M0 * temp4 + temp0 * temp5));
//    const double C1_c = 0;
    const double C2_c = 2 * Kc * (M1 * M1 + temp1 * temp6 + Kcp * (M1 * temp1 + temp0 * temp6));

    const double C0 = C0_fm * C0_c / (C0_fm + C0_c);
    const double C1 = 0;
    const double C2 = C2_fm * C2_c / (C2_fm + C2_c);

    const vector<double> sootSourceTerms = {(N0 + G0 + Cnd0 - X0 + C0),
											(N1 + G1 + Cnd1 - X1 + C1),
											(N2 + G2 + Cnd2 - X2 + C2)};

    //---------- get gas source terms

    map<GasSpecies, double> gasSourceTerms = getGasSourceTerms(state, massRateRatios, N1, G1, X1, Cnd1);
    map<size_t, double> PAHSourceTerms = getPAHSourceTerms(state, massRateRatios, N1, 0, X1, Cnd1);

    return SourceTerms(sootSourceTerms, gasSourceTerms, PAHSourceTerms);
}
double SootModel_LOGN::Mk(double k, double M0, double M1, double M2) {
    const double M0_exp = 1 + 0.5 * k * (k - 3);
    const double M1_exp = k * (2 - k);
    double M2_exp = 0.5 * k * (k - 1);

    if (M2 == 0 && M2_exp < 0)
        M2_exp = 0;
    
    return pow(M0, M0_exp) * pow(M1, M1_exp) * pow(M2, M2_exp);
}
////////////////////////////////////////////////////////////////////////////////
/*! Kfm
 *      Returns continuum coagulation coefficient Kc prime
 *      Call set_gas_state_vars first.
 */
double SootModel_LOGN::getKfm(const State& state)
{
	return eps_c * sqrt(M_PI * kb * state.getT() / 2) * pow(6 / M_PI / state.getRhoSoot(), 2 / 3.0);
}
////////////////////////////////////////////////////////////////////////////////
/*! Kc
 *      Returns continuum coagulation coefficient Kc
 *      Call set_gas_state_vars first.
 */
double SootModel_LOGN::getKc(const State& state)
{
	return 2 * kb * state.getT() / (3 / state.getMuGas());
}
////////////////////////////////////////////////////////////////////////////////
/*! Kcp
 *      Returns continuum coagulation coefficient Kc prime
 *      Call set_gas_state_vars first.
 */
double SootModel_LOGN::getKcp(const State& state)
{
	return 2 * 1.657 * state.getGasMeanFreePath() * pow(M_PI / 6 * state.getRhoSoot(), 1.0 / 3);
}
