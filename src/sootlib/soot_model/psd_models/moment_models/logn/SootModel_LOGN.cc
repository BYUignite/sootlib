#include "SootModel_LOGN.h"

#include "sootlib/soot_model/static.h"

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

    const double Kfm = get_Kfm(state);
    const double Kc = get_Kc(state);
    const double Kcp = get_Kcp(state);

    const double mmin = state.getCMin() * MW_C / Na;

    MassRateRatios massRateRatios;

    double Jnuc;
    if (nucleationModel->getMechanism() != NucleationMechanism::PAH) {
        Jnuc = nucleationModel->getNucleationRate(state, {}, {}, massRateRatios);
    }
    else {
        const double Ifm = Kfm * b_coag * (M0 * pow(state.getMDimer(), 1.0 / 6)
        	+ 2 * Mk_LOGN(1.0 / 3, M0, M1, M2) * pow(state.getMDimer(), -1.0 / 6)
        	+ Mk_LOGN(2.0 / 3, M0, M1, M2) * pow(state.getMDimer(), -1.0 / 2)
        	+ Mk_LOGN(-1.0 / 2, M0, M1, M2) * pow(state.getMDimer(), 2.0 / 3)
        	+ 2 * Mk_LOGN(-1.0 / 6, M0, M1, M2) * pow(state.getMDimer(), 1.0 / 3)
        	+ Mk_LOGN(1.0 / 6, M0, M1, M2));
        const double Ic = Kc * (2 * M0 + Mk_LOGN(-1.0 / 3, M0, M1, M2) * pow(state.getMDimer(), 1.0 / 3)
        	+ Mk_LOGN(1.0 / 3, M0, M1, M2) * pow(state.getMDimer(), -1.0 / 3)
        	+ Kcp * (M0 * pow(state.getMDimer(), -1.0 / 3)
        	+ Mk_LOGN(-1.0 / 3, M0, M1, M2)
        	+ Mk_LOGN(1.0 / 3, M0, M1, M2) * pow(state.getMDimer(), -2.0 / 3)
        	+ Mk_LOGN(-2.0 / 3, M0, M1, M2) * pow(state.getMDimer(), 1.0 / 3)));

        const double beta_DD = coagulationModel->getCoagulationRate(state, state.getMDimer(), state.getMDimer());
        // TODO this might not be the right DIMER
        Jnuc = 0.5 * beta_DD * state.getDimer() * state.getDimer();

        const double Ifm1 = Ifm;
        const double Ifm2 = Kfm * b_coag * (M1 * pow(state.getMDimer(), 1.0 /6)
        	+ 2 * Mk_LOGN(4.0 / 3, M0, M1, M2) * pow(state.getMDimer(), -1.0 / 6)
        	+ Mk_LOGN(5.0 / 3, M0, M1, M2) * pow(state.getMDimer(), -1.0 / 2)
        	+ Mk_LOGN(1.0 / 2, M0, M1, M2) * pow(state.getMDimer(), 2.0 / 3)
        	+ 2 * Mk_LOGN(5.0 / 6, M0, M1, M2) * pow(state.getMDimer(), 1.0 / 3)
        	+ Mk_LOGN(7.0 / 6, M0, M1, M2));
        const double Ic1 = Ic;
        const double Ic2 = Kc * (2 * M1 + Mk_LOGN(2.0 / 3, M0, M1, M2) * pow(state.getMDimer(), 1.0 / 3)
        	+ Mk_LOGN(4.0 / 3, M0, M1, M2) * pow(state.getMDimer(), -1.0 / 3)
        	+ Kcp * (M1 * pow(state.getMDimer(), -1.0 / 3)
        	+ Mk_LOGN(2.0 / 3, M0, M1, M2)
        	+ Mk_LOGN(4.0 / 3, M0, M1, M2) * pow(state.getMDimer(), -2.0 / 3)
        	+ Mk_LOGN(1.0 / 3, M0, M1, M2) * pow(state.getMDimer(), 1.0 / 3)));

        Cnd1 = state.getMDimer() * state.getDimer() * (Ic1 * Ifm1) / (Ic1 + Ifm1);
        Cnd2 = 2 * state.getMDimer() * state.getDimer() * (Ic2 * Ifm2) / (Ic2 + Ifm2);
    }

    const double N0 = Jnuc, N1 = Jnuc * mmin, N2 = Jnuc * mmin * mmin;

    const double Kgrw = growthModel->getGrowthRate(state, massRateRatios);

    const double term = Kgrw * M_PI * pow(6 / state.getRhoSoot() / M_PI, 2.0 / 3);

    const double G0 = 0, G1 = term * Mk_LOGN(2.0 / 3, M0, M1, M2), G2 = term * Mk_LOGN(5.0 / 3, M0, M1, M2);

    const double Koxi = oxidationModel->getOxidationRate(state, massRateRatios);

    const double X0 = 0;
    const double X1 = Koxi * M_PI * pow(6.0 / state.getRhoSoot() / M_PI, 2.0 / 3) * Mk_LOGN(2.0 / 3, M0, M1, M2);
    const double X2 = Koxi * M_PI * pow(6.0 / state.getRhoSoot() / M_PI, 2.0 / 3) * Mk_LOGN(5.0 / 3, M0, M1, M2) * 2;

    const double C0_fm = -Kfm * b_coag * (M0 * Mk_LOGN(1.0 / 6, M0, M1, M2)
    	+ 2 * Mk_LOGN(1.0 / 3, M0, M1, M2) * Mk_LOGN(-1.0 / 6, M0, M1, M2)
    	+ Mk_LOGN(2.0 / 3, M0, M1, M2) * Mk_LOGN(-1.0 / 2, M0, M1, M2));
//    const double C1_fm = 0;
    const double C2_fm = 2 * Kfm * b_coag * (M1 * Mk_LOGN(7.0 / 6, M0, M1, M2)
    	+ 2 * Mk_LOGN(4.0 / 3, M0, M1, M2) * Mk_LOGN(5.0 / 6, M0, M1, M2)
    	+ Mk_LOGN(5.0 / 3, M0, M1, M2) * Mk_LOGN(1.0 / 2, M0, M1, M2));

    const double C0_c = -Kc * (M0 * M0 + Mk_LOGN(1.0 / 3, M0, M1, M2) * Mk_LOGN(-1.0 / 3, M0, M1, M2)
    	+ Kcp * (M0 * Mk_LOGN(-1.0 / 3, M0, M1, M2)
    	+ Mk_LOGN(1.0 / 3, M0, M1, M2) * Mk_LOGN(-2.0 / 3, M0, M1, M2)));
//    const double C1_c = 0;
    const double C2_c = 2 * Kc * (M1 * M1 + Mk_LOGN(2.0 / 3, M0, M1, M2) * Mk_LOGN(4.0 / 3, M0, M1, M2) + Kcp * (M1 * Mk_LOGN(2.0 / 3, M0, M1, M2) + Mk_LOGN(1.0 / 3, M0, M1, M2) * Mk_LOGN(4.0 / 3, M0, M1, M2)));

    const double C0 = C0_fm * C0_c / (C0_fm + C0_c);
    const double C1 = 0;
    const double C2 = C2_fm * C2_c / (C2_fm + C2_c);

    const vector<double> sootSourceTerms = {(N0 + G0 + Cnd0 - X0 + C0),
											(N1 + G1 + Cnd1 - X1 + C1),
											(N2 + G2 + Cnd2 - X2 + C2)};

    //---------- get gas source terms

    map<GasSpecies, double> gasSourceTerms;
    map<size_t, double> PAHSourceTerms;

    // Nucleation
    for (auto it = massRateRatios.nucCond().gasSpeciesBegin(); it != massRateRatios.nucCond().gasSpeciesEnd(); it++)
        gasSourceTerms[it->first] += N1 * it->second / state.getRhoGas();
    for (auto it = massRateRatios.nucCond().PAHBegin(); it != massRateRatios.nucCond().PAHEnd(); it++)
        PAHSourceTerms[it->first] += N1 * it->second / state.getRhoGas();

    // Growth
    for (auto it = massRateRatios.groOxi().gasSpeciesBegin(); it != massRateRatios.groOxi().gasSpeciesEnd(); it++)
        gasSourceTerms[it->first] += G1 * it->second / state.getRhoGas();

    // Oxidation
    for (auto it = massRateRatios.groOxi().gasSpeciesBegin(); it != massRateRatios.groOxi().gasSpeciesEnd(); it++)
        gasSourceTerms[it->first] += X1 * it->second / state.getRhoGas();
    for (auto it = massRateRatios.groOxi().PAHBegin(); it != massRateRatios.groOxi().PAHEnd(); it++)
        PAHSourceTerms[it->first] += X1 * it->second / state.getRhoGas();

    // PAH condensation
    for (auto it = massRateRatios.groOxi().gasSpeciesBegin(); it != massRateRatios.groOxi().gasSpeciesEnd(); it++)
        gasSourceTerms[it->first] += Cnd1 * it->second / state.getRhoGas();
    for (auto it = massRateRatios.nucCond().PAHBegin(); it != massRateRatios.nucCond().PAHEnd(); it++)
        PAHSourceTerms[it->first] += Cnd1 * it->second / state.getRhoGas();

    // Coagulation - n/a

    return SourceTerms(sootSourceTerms, gasSourceTerms, PAHSourceTerms);
}
double SootModel_LOGN::Mk_LOGN(double k, double M0, double M1, double M2) {
    double M0_exp = 1 + 0.5 * k * (k - 3);
    double M1_exp = k * (2 - k);
    double M2_exp = 0.5 * k * (k - 1);
    
    if (M2 == 0 && M2_exp < 0)
        M2_exp = 0;
    
    return pow(M0, M0_exp) * pow(M1, M1_exp) * pow(M2, M2_exp);
}
