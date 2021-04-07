#include "SootModel_SECT.h"

using namespace std;
using namespace soot;

SootModel_SECT* SootModel_SECT::getInstance(unique_ptr<CoagulationModel> coagulationModel,
                                            unique_ptr<GrowthModel> growthModel,
                                            unique_ptr<NucleationModel> nucleationModel,
                                            unique_ptr<OxidationModel> oxidationModel) {
    return new SootModel_SECT(move(coagulationModel),
                              move(growthModel),
                              move(nucleationModel),
                              move(oxidationModel));
}
SootModel_SECT::SootModel_SECT(unique_ptr<CoagulationModel> coagulationModel,
                               unique_ptr<GrowthModel> growthModel,
                               unique_ptr<NucleationModel> nucleationModel,
                               unique_ptr<OxidationModel> oxidationModel) : SootChemistry(move(coagulationModel),
                                                                                          move(growthModel),
                                                                                          move(nucleationModel),
                                                                                          move(oxidationModel)) {}
SourceTerms SootModel_SECT::getSourceTerms(State& state) const {
    // FIXME this actually might be a bin model?

    MassRateRatios massRateRatios;
    vector<double> wts = state.getBinsConst();
    vector<double> absc(state.getNumBins(), 0);

    for (size_t k = 0; k < state.getNumBins(); k++)
        absc.at(k) = state.getCMin() * pow(2.0, k) * MW_C / Na;

    for (double& num : wts) {
        if (num < 0)
            num = 0;
    }

    const double Jnuc = nucleationModel->getNucleationRate(state, absc, wts, massRateRatios);
    vector<double> Kgrw(state.getNumBins(), 0);
    for (double& num : Kgrw)
        num = growthModel->getGrowthRate(state, massRateRatios); // FIXME the old code wants to use stuff with wts and absc
    vector<double> Koxi(state.getNumBins(), 0);
    for (double& num : Koxi)
        num = oxidationModel->getOxidationRate(state, massRateRatios); // FIXME the old code also wants to do different stuff with these too

    vector<double> Coag(state.getNumBins(), 0);
    double leaving;
    vector<double> divided;
    for (size_t i = 0; i < Coag.size(); i++) {
        for (size_t j = 0; j < Coag.size(); j++) {
            leaving = 0.5 * coagulationModel->getCoagulationRate(state, absc.at(i), absc.at(j)) * wts.at(i) * wts.at(i);
            Coag.at(i) -= leaving;
            Coag.at(j) -= leaving;
            divided = getDivision((state.getBin(i) + state.getBin(j)), leaving, absc);
            for (size_t k = 0; k < Coag.size(); k++) {
                Coag.at(k) += divided.at(k);
            }
        }
    }

    vector<double> N0(state.getNumBins(), 0);
    N0.at(0) = Jnuc;
    const double N_tot = Jnuc * state.getCMin() * MW_C / Na;

    vector<double> Cnd0(state.getNumBins(), 0);
    double Cnd_tot = 0;
    if (nucleationModel->getMechanism() == NucleationMechanism::PAH) {
        for (size_t i = 0; i < Cnd0.size(); i++) {
            Cnd0.at(i) = state.getDimer() * state.getMDimer() * coagulationModel->getCoagulationRate(state, state.getMDimer(), absc.at(i)) * wts.at(i);
            Cnd_tot += Cnd0.at(i) * absc.at(i);
        }
    }

    vector<double> Am2m3(state.getNumBins(), 0);
    for (size_t i = 0; i < state.getNumBins(); i++) {
        if (wts.at(i) > 0)
            Am2m3.at(i) = M_PI * pow(abs(6.0 / (M_PI * state.getRhoSoot()) * state.getBin(i)), 2.0 / 3) * abs(wts.at(i));
    }
    vector<double> G0(state.getNumBins(), 0);
    double G_tot = 0;
    double Ngrw;
    for (size_t i = 0; i < state.getNumBins(); i++) {
        if (i == 0)
            Ngrw = -Kgrw.at(i) * Am2m3.at(i) * wts.at(i) / (absc.at(i + 1) - absc.at(i));
        else if (i == (state.getNumBins() - 1))
            Ngrw = Kgrw.at(i - 1) * Am2m3.at(i - 1) * wts.at(i - 1) / (absc.at(i) - absc.at(i - 1));
        else
            Ngrw = Kgrw.at(i - 1) * Am2m3.at(i - 1) * wts.at(i - 1) / (absc.at(i) - absc.at(i - 1)) - Kgrw.at(i) * Am2m3.at(i) * wts.at(i) / (absc.at(i + 1) - absc.at(i));

        G0.at(i) = Ngrw;
        G_tot += Ngrw * absc.at(i);
    }

    vector<double> X0(state.getNumBins(), 0);
    double X_tot = 0;
    double Noxi;
    for (size_t i = 0; i < state.getNumBins(); i++) {
        if (i == 0)
            Noxi = Koxi.at(i) * Am2m3.at(i) * wts.at(i) / (absc.at(i + 1) - absc.at(i));
        else if (i == (state.getNumBins() - 1))
            Noxi = -Koxi.at(i - 1) * Am2m3.at(i - 1) * wts.at(i - 1) / (absc.at(i) - absc.at(i - 1));
        else
            Noxi = -Koxi.at(i - 1) * Am2m3.at(i - 1) * wts.at(i - 1) / (absc.at(i) - absc.at(i - 1)) + Koxi.at(i) * Am2m3.at(i) * wts.at(i) / (absc.at(i + 1) - absc.at(i));

        X0.at(i) = Noxi;
        X_tot += Noxi * absc.at(i);
    }

    vector<double> C0 = Coag;

    vector<double> sootSourceTerms(state.getNumBins(), 0);
    for (size_t i = 0; i < sootSourceTerms.size(); i++)
        sootSourceTerms.at(i) = (N0.at(i) + Cnd0.at(i) + G0.at(i) + X0.at(i) + C0.at(i)) / state.getRhoSoot();

    // There was a commented out section in the old code here labeled "computer gas source terms", but it looked like it didn't do anything anymore

    //---------- get gas source terms

    map<GasSpecies, double> gasSourceTerms;
    map<size_t, double> PAHSourceTerms;

    // Nucleation
    for (auto it = massRateRatios.nucCond().gasSpeciesBegin(); it != massRateRatios.nucCond().gasSpeciesEnd(); it++)
        gasSourceTerms[it->first] += N_tot * it->second / state.getRhoGas();
    for (auto it = massRateRatios.nucCond().PAHBegin(); it != massRateRatios.nucCond().PAHEnd(); it++)
        PAHSourceTerms[it->first] += N_tot * it->second / state.getRhoGas();

    // Growth
    for (auto it = massRateRatios.groOxi().gasSpeciesBegin(); it != massRateRatios.groOxi().gasSpeciesEnd(); it++)
        gasSourceTerms[it->first] += G_tot * it->second / state.getRhoGas();

    // Oxidation
    for (auto it = massRateRatios.groOxi().gasSpeciesBegin(); it != massRateRatios.groOxi().gasSpeciesEnd(); it++)
        gasSourceTerms[it->first] += X_tot * it->second / state.getRhoGas();
    for (auto it = massRateRatios.groOxi().PAHBegin(); it != massRateRatios.groOxi().PAHEnd(); it++)
        PAHSourceTerms[it->first] += X_tot * it->second / state.getRhoGas();

    // PAH condensation
    for (auto it = massRateRatios.groOxi().gasSpeciesBegin(); it != massRateRatios.groOxi().gasSpeciesEnd(); it++)
        gasSourceTerms[it->first] += Cnd_tot * it->second / state.getRhoGas();
    for (auto it = massRateRatios.nucCond().PAHBegin(); it != massRateRatios.nucCond().PAHEnd(); it++)
        PAHSourceTerms[it->first] += Cnd_tot * it->second / state.getRhoGas();

    // Coagulation - n/a

    return SourceTerms(sootSourceTerms, gasSourceTerms, PAHSourceTerms);
}
vector<double> SootModel_SECT::getDivision(double mass, double num, const vector<double>& absc) {
    int loc = 0;
    bool found = false;
    vector<double> toReturn(absc.size(), 0);
    while (!found) {
        loc++;
        if (loc >= absc.size()) {
            loc = absc.size() - 1;
            found = true;
        }
        if (absc.at(loc) > mass)
            found = true;
    }

    const double right = (mass - absc.at(loc - 1)) / (absc.at(loc) - absc.at(loc - 1)) * num;
    const double left = (absc.at(loc) - mass) / (absc.at(loc) - absc.at(loc - 1)) * num;
    toReturn.at(loc - 1) += left;
    toReturn.at(loc) += right;

    return toReturn;
}
