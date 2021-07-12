#include "psdModel_SECT.h"

using namespace std;
using namespace soot;

psdModel_SECT::psdModel_SECT(size_t n) {

    if (n < 1)
        throw runtime_error("Invalid number of soot moments requested");

    this->nBins = n;

    // initialize sourceTerms soot variable
    for (int i=0; i<nBins; i++)
        sourceTerms->sootSourceTerms.push_back(0);
}

void psdModel_SECT::getSourceTermsImplementation(state& state, std::ostream* out) const {

    if (out) {
        *out << " === [SootModel SECT] ===" << endl;
        *out << endl;
    }

    vector<double> wts(nBins, 0);
    vector<double> absc(nBins, 0);

    for (size_t k = 0; k < nBins; k++)
        absc.at(k) = state.cMin * pow(2, k) * gasSpMW.at(gasSp::C) / Na;

    for (double& num : wts) {
        if (num < 0)
            num = 0;
    }

    if (out) {
        *out << "weights (" << wts.size() << ")" << endl;
        for (size_t i = 0; i < wts.size(); i++)
            *out << i << ": " << wts.at(i) << endl;
        *out << "abscissas (" << absc.size() << ")" << endl;
        for (size_t i = 0; i < absc.size(); i++)
            *out << i << ": " << absc.at(i) << endl;
        *out << endl;
    }

    // FIXME this code is likely incorrect
    const double Jnuc = sootModel.nuc->getNucleationSootRate(state, absc, wts);

    if (out) {
        *out << "Jnuc: " << Jnuc << endl;
        *out << endl;
    }

    vector<double> Kgrw(nBins, 0);
    for (double& num : Kgrw)
        num = sootModel.grw->getGrowthSootRate(state); // FIXME the old code wants to use stuff with wts and absc as inputs
        // this is not how the growth model is treated anywhere else and it doesn't really work that way in this setup

    if (out) {
        *out << "Kgrw (" << Kgrw.size() << ")" << endl;
        for (size_t i = 0; i < Kgrw.size(); i++)
            *out << i << ": " << Kgrw.at(i) << endl;
        *out << endl;
    }

    vector<double> Koxi(nBins, 0);
    for (double& num : Koxi)
        num = sootModel.oxi->getOxidationSootRate(state); // FIXME the old code also wants to do different stuff with these too
        // this is not how the oxidation model is treated anywhere else and it doesn't really work that way in this setup

    if (out) {
        *out << "Koxi (" << Koxi.size() << ")" << endl;
        for (size_t i = 0; i < Koxi.size(); i++)
            *out << i << ": " << Koxi.at(i) << endl;
        *out << endl;
    }

    vector<double> Coag(nBins, 0);
    double leaving;
    vector<double> divided;
    for (size_t i = 0; i < Coag.size(); i++) {
        for (size_t j = 0; j < Coag.size(); j++) {
            leaving = 0.5 * sootModel.coa->getCoagulationRate(state, absc.at(i), absc.at(j)) * wts.at(i) * wts.at(i);
            Coag.at(i) -= leaving;
            Coag.at(j) -= leaving;
            divided = getDivision((state.sootVar[i] + state.sootVar[j]), leaving, absc);
            for (size_t k = 0; k < Coag.size(); k++)
                Coag.at(k) += divided.at(k);
        }
    }

    if (out) {
        *out << "Coag (" << Coag.size() << ")" << endl;
        for (size_t i = 0; i < Coag.size(); i++)
            *out << i << ": " << Coag.at(i) << endl;
        *out << endl;
    }

    vector<double> N0(state.nBins, 0);
    N0.at(0) = Jnuc;
    const double N_tot = Jnuc * state.cMin * gasSpMW.at(gasSp::C) / Na;

    if (out) {
        *out << "N0 (" << N0.size() << ")" << endl;
        for (size_t i = 0; i < N0.size(); i++)
            *out << i << ": " << N0.at(i) << endl;
        *out << "N tot: " << N_tot << endl;
        *out << endl;
    }

    vector<double> Cnd0(state.nBins, 0);
    double Cnd_tot = 0;
    if (sootModel.nuc->getMechanism() == nucleationMech::PAH) {
        for (size_t i = 0; i < Cnd0.size(); i++) {
            Cnd0.at(i) = state.getDimer() * state.getMDimer() * sootModel.coa->getCoagulationRate(state, state.getMDimer(), absc.at(i)) * wts.at(i);
            Cnd_tot += Cnd0.at(i) * absc.at(i);
        }
    }

    if (out) {
        *out << "Cnd0 (" << Cnd0.size() << ")" << endl;
        for (size_t i = 0; i < Cnd0.size(); i++)
            *out << i << ": " << Cnd0.at(i) << endl;
        *out << "Cnd tot: " << Cnd_tot << endl;
        *out << endl;
    }

    vector<double> Am2m3(nBins, 0);
    for (size_t i = 0; i < nBins; i++) {
        if (wts.at(i) > 0)
            Am2m3.at(i) = M_PI * pow(abs(6 / (M_PI * rhoSoot) * state.sootVar[i]), 2.0 / 3) * abs(wts.at(i));
    }

    if (out) {
        *out << "Am2m3 (" << Am2m3.size() << ")" << endl;
        for (size_t i = 0; i < Am2m3.size(); i++)
            *out << i << ": " << Am2m3.at(i) << endl;
        *out << endl;
    }

    vector<double> G0(nBins, 0);
    double G_tot = 0;
    double Ngrw;
    for (size_t i = 0; i < nBins; i++) {
        if (i == 0)
            Ngrw = -Kgrw.at(i) * Am2m3.at(i) * wts.at(i) / (absc.at(i + 1) - absc.at(i));
        else if (i == (nBins - 1))
            Ngrw = Kgrw.at(i - 1) * Am2m3.at(i - 1) * wts.at(i - 1) / (absc.at(i) - absc.at(i - 1));
        else
            Ngrw = Kgrw.at(i - 1) * Am2m3.at(i - 1) * wts.at(i - 1) / (absc.at(i) - absc.at(i - 1)) - Kgrw.at(i) * Am2m3.at(i) * wts.at(i) / (absc.at(i + 1) - absc.at(i));

        G0.at(i) = Ngrw;
        G_tot += Ngrw * absc.at(i);
    }

    if (out) {
        *out << "G0 (" << G0.size() << ")" << endl;
        for (size_t i = 0; i < G0.size(); i++)
            *out << i << ": " << G0.at(i) << endl;
        *out << "G tot: " << G_tot << endl;
        *out << endl;
    }

    vector<double> X0(nBins, 0);
    double X_tot = 0;
    double Noxi;
    for (size_t i = 0; i < nBins; i++) {
        if (i == 0)
            Noxi = Koxi.at(i) * Am2m3.at(i) * wts.at(i) / (absc.at(i + 1) - absc.at(i));
        else if (i == (nBins - 1))
            Noxi = -Koxi.at(i - 1) * Am2m3.at(i - 1) * wts.at(i - 1) / (absc.at(i) - absc.at(i - 1));
        else
            Noxi = -Koxi.at(i - 1) * Am2m3.at(i - 1) * wts.at(i - 1) / (absc.at(i) - absc.at(i - 1)) + Koxi.at(i) * Am2m3.at(i) * wts.at(i) / (absc.at(i + 1) - absc.at(i));

        X0.at(i) = Noxi;
        X_tot += Noxi * absc.at(i);
    }

    if (out) {
        *out << "X0 (" << X0.size() << ")" << endl;
        for (size_t i = 0; i < X0.size(); i++)
            *out << i << ": " << X0.at(i) << endl;
        *out << "X tot: " << X_tot << endl;
        *out << endl;
    }

    vector<double>& C0 = Coag;

    vector<double> sootSourceTerms(nBins, 0);
    for (size_t i = 0; i < sootSourceTerms.size(); i++)
        sootSourceTerms.at(i) = (N0.at(i) + Cnd0.at(i) + G0.at(i) + X0.at(i) + C0.at(i)) / rhoSoot;

    if (out) {
        *out << "Soot Source Terms (" << sootSourceTerms.size() << ")" << endl;
        for (size_t i = 0; i < sootSourceTerms.size(); i++)
            *out << i << ": " << sootSourceTerms.at(i) << endl;
        *out << endl;
    }

    // There was a commented out section in the old code here labeled "computer gas source terms", but it looked like it didn't do anything anymore

    //---------- get gas source terms

    map<gasSp, double> gasSourceTerms = sootChemistry.getGasSourceTerms(state, massRateRatios, N_tot, G_tot, X_tot, Cnd_tot);
    map<size_t, double> PAHSourceTerms = sootChemistry.getPAHSourceTerms(state, massRateRatios, N_tot, 0, X_tot, Cnd_tot);

    if (out) {
        *out << "Gas Source Terms (" << gasSourceTerms.size() << ")" << endl;
        for (const auto& [g, t] : gasSourceTerms)
            *out << (int) g << ": " << t << endl;
        *out << "PAH Source Terms (" << PAHSourceTerms.size() << ")" << endl;
        for (const auto& [s, t] : PAHSourceTerms)
            *out << s << ": " << t << endl;
        *out << endl;
    }


    return sourceTermStruct(sootSourceTerms, gasSourceTerms, PAHSourceTerms);
}
vector<double> psdModel_SECT::getDivision(double mass, double num, const vector<double>& absc) {
    size_t loc = 0;
    bool found = false;
    vector<double> toReturn(absc.size(), 0);
    while (!found) {
        loc++;
        if (loc >= absc.size()) {
            loc = absc.size() - 1;  // FIXME this is the problematic statement, it doesn't account for the scenario where the size of absc is 1 or less
            found = true;  // TODO I think it would probably be more appropriate to have a break here
        }
        if (absc.at(loc) > mass)
            found = true;
    }

    // FIXME it's possible for loc to be 0 here, which is a problem
    const double right = (mass - absc.at(loc - 1)) / (absc.at(loc) - absc.at(loc - 1)) * num;
    const double left = (absc.at(loc) - mass) / (absc.at(loc) - absc.at(loc - 1)) * num;
    toReturn.at(loc - 1) += left;
    toReturn.at(loc) += right;

    return toReturn;
}
void psdModel_SECT::checkState(const state& state) const {
    if (nBins < 1)
        throw runtime_error("SECT soot model requires 1+ sections/bins");
}
