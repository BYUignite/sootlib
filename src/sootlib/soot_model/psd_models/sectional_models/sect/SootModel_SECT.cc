#include "SootModel_SECT.h"

#include <cmath>

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
    MassRateRatios massRateRatios;
    vector<double> wts = state.getSectionsConst();
    vector<double> absc(state.getNumSections(), 0);

    for (size_t k = 0; k < state.getNumSections(); k++)
        absc.at(k) = state.getCMin() * pow(2.0, k) * MW_C / Na;

    for (double& num : wts) {
        if (num < 0)
            num = 0;
    }

    // FIXME this code is likely incorrect
    const double Jnuc = nucleationModel->getNucleationRate(state, absc, wts, massRateRatios);
    vector<double> Kgrw(state.getNumSections(), 0);
    for (double& num : Kgrw)
        num = growthModel->getGrowthRate(state, massRateRatios); // FIXME the old code wants to use stuff with wts and absc as inputs
        // this is not how the growth model is treated anywhere else and it doesn't really work that way in this setup
    vector<double> Koxi(state.getNumSections(), 0);
    for (double& num : Koxi)
        num = oxidationModel->getOxidationRate(state, massRateRatios); // FIXME the old code also wants to do different stuff with these too
        // this is not how the oxidation model is treated anywhere else and it doesn't really work that way in this setup

    vector<double> Coag(state.getNumSections(), 0);
    double leaving;
    vector<double> divided;
    for (size_t i = 0; i < Coag.size(); i++) {
        for (size_t j = 0; j < Coag.size(); j++) {
            leaving = 0.5 * coagulationModel->getCoagulationRate(state, absc.at(i), absc.at(j)) * wts.at(i) * wts.at(i);
            Coag.at(i) -= leaving;
            Coag.at(j) -= leaving;
            divided = getDivision((state.getSection(i) + state.getSection(j)), leaving, absc);
            for (size_t k = 0; k < Coag.size(); k++)
                Coag.at(k) += divided.at(k);
        }
    }

    vector<double> N0(state.getNumSections(), 0);
    N0.at(0) = Jnuc;
    const double N_tot = Jnuc * state.getCMin() * MW_C / Na;

    vector<double> Cnd0(state.getNumSections(), 0);
    double Cnd_tot = 0;
    if (nucleationModel->getMechanism() == NucleationMechanism::PAH) {
        for (size_t i = 0; i < Cnd0.size(); i++) {
            Cnd0.at(i) = state.getDimer() * state.getMDimer() * coagulationModel->getCoagulationRate(state, state.getMDimer(), absc.at(i)) * wts.at(i);
            Cnd_tot += Cnd0.at(i) * absc.at(i);
        }
    }

    vector<double> Am2m3(state.getNumSections(), 0);
    for (size_t i = 0; i < state.getNumSections(); i++) {
        if (wts.at(i) > 0)
            Am2m3.at(i) = M_PI * pow(abs(6 / (M_PI * state.getRhoSoot()) * state.getSection(i)), 2.0 / 3) * abs(wts.at(i));
    }
    vector<double> G0(state.getNumSections(), 0);
    double G_tot = 0;
    double Ngrw;
    for (size_t i = 0; i < state.getNumSections(); i++) {
        if (i == 0)
            Ngrw = -Kgrw.at(i) * Am2m3.at(i) * wts.at(i) / (absc.at(i + 1) - absc.at(i));
        else if (i == (state.getNumSections() - 1))
            Ngrw = Kgrw.at(i - 1) * Am2m3.at(i - 1) * wts.at(i - 1) / (absc.at(i) - absc.at(i - 1));
        else
            Ngrw = Kgrw.at(i - 1) * Am2m3.at(i - 1) * wts.at(i - 1) / (absc.at(i) - absc.at(i - 1)) - Kgrw.at(i) * Am2m3.at(i) * wts.at(i) / (absc.at(i + 1) - absc.at(i));

        G0.at(i) = Ngrw;
        G_tot += Ngrw * absc.at(i);
    }

    vector<double> X0(state.getNumSections(), 0);
    double X_tot = 0;
    double Noxi;
    for (size_t i = 0; i < state.getNumSections(); i++) {
        if (i == 0)
            Noxi = Koxi.at(i) * Am2m3.at(i) * wts.at(i) / (absc.at(i + 1) - absc.at(i));
        else if (i == (state.getNumSections() - 1))
            Noxi = -Koxi.at(i - 1) * Am2m3.at(i - 1) * wts.at(i - 1) / (absc.at(i) - absc.at(i - 1));
        else
            Noxi = -Koxi.at(i - 1) * Am2m3.at(i - 1) * wts.at(i - 1) / (absc.at(i) - absc.at(i - 1)) + Koxi.at(i) * Am2m3.at(i) * wts.at(i) / (absc.at(i + 1) - absc.at(i));

        X0.at(i) = Noxi;
        X_tot += Noxi * absc.at(i);
    }

    vector<double> C0 = Coag;

    vector<double> sootSourceTerms(state.getNumSections(), 0);
    for (size_t i = 0; i < sootSourceTerms.size(); i++)
        sootSourceTerms.at(i) = (N0.at(i) + Cnd0.at(i) + G0.at(i) + X0.at(i) + C0.at(i)) / state.getRhoSoot();

    // There was a commented out section in the old code here labeled "computer gas source terms", but it looked like it didn't do anything anymore

    //---------- get gas source terms

    map<GasSpecies, double> gasSourceTerms = getGasSourceTerms(state, massRateRatios, N_tot, G_tot, X_tot, Cnd_tot);
    map<size_t, double> PAHSourceTerms = getPAHSourceTerms(state, massRateRatios, N_tot, 0, X_tot, Cnd_tot);

    return SourceTerms(sootSourceTerms, gasSourceTerms, PAHSourceTerms);
}
vector<double> SootModel_SECT::getDivision(double mass, double num, const vector<double>& absc) {
    size_t loc = 0;
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
