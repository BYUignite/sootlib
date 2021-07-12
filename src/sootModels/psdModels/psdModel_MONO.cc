#include "psdModel_MONO.h"

using namespace std;
using namespace soot;

psdModel_MONO::psdModel_MONO(size_t n) {

    // warn user if wrong number of soot moments is requested
    if (n != 2)
        cerr << "Invalid number of soot moments requested. MONO model will use default value of 2 soot moments." << endl;

    // specify number of soot moments for MONO model
    this->nMom = 2;

    // initialize sourceTerms soot variable
    for (int i=0; i<nMom; i++)
        sourceTerms->sootSourceTerms.push_back(0);

}

////////////////////////////////////////////////////////////////////////////////
/** getSourceTermsImplementation function
 *  
 *      Calculates soot source terms using monodispersed PSD model (MONO).
 *      Returns soot, gas, and PAH source terms (where applicable). 
 *
 *      @param  state    \input     thermodynamic state object
 *
 */

void psdModel_MONO::getSourceTermsImplementation(state& state, std::ostream* out) const {

    if (out) {
        *out << " === [SootModel MONO] ===" << endl;
        *out << endl;
    }

    vector<double> weights = {0};
    vector<double> abscissas = {0};

    //---------- get moments

    double M0 = state.sootVar[0];
    double M1 = state.sootVar[1];

    //---------- set weights and abscissas

    if (M0 > 0) {
        weights.at(0) = M0;
        abscissas.at(0) = M1 / M0;
    }

    //---------- get chemical rates

    double jNuc = nuc->getNucleationSootRate(state, abscissas, weights);
    double kGrw = grw->getGrowthSootRate(state);
    double kOxi = oxi->getOxidationSootRate(state);
    double coag = coa->getCoagulationSootRate(state, abscissas.at(0), abscissas.at(0));

    if (out) {
        *out << "jNuc: " << jNuc << endl;
        *out << "kGrw: " << kGrw << endl;
        *out << "kOxi: " << kOxi << endl;
        *out << "coag: " << coag << endl;
        *out << endl;
    }

    //---------- nucleation terms

    double N0 = jNuc;
    double N1 = jNuc * state.cMin * gasSpMW.at(gasSp::C) / Na;

    if (out) {
        *out << "N0: " << N0 << endl;
        *out << "N1: " << N1 << endl;
        *out << endl;
    }

    //---------- PAH condensation terms

    double Cnd0 = 0;
    double Cnd1 = 0;

    if (sootModel::nucleationMechanism == nucleationMech::PAH) {

        double nDimer = nuc->nDimer;
        double mDimer = nuc->mDimer;

        Cnd1 = nDimer * mDimer * coa->getCoagulationSootRate(state, mDimer, abscissas.at(0)) * weights.at(0);


    }
//    const double Cnd1 = sootModel.nucleationMechanism == nucleationMech::PAH ? state.getDimer() * state.getMDimer() * sootChemistry.coagulationModel->getCoagulationRate(state, state.getMDimer(), abscissas.at(0)) * weights.at(0) : 0;
//    double Cnd1 = sootModel.nucleationMechanism == nucleationMech::PAH ? sootModel.nuc->nDimer * sootModel.nuc->mDimer * sootModel.coa->getCoagulationRate(state, sootModel.nuc->mDimer, abscissas.at(0)) * weights.at(0) : 0;

    if (out) {
        *out << "Cnd0: " << Cnd0 << endl;
        *out << "Cnd1: " << Cnd1 << endl;
        *out << endl;
    }

    //---------- growth terms

    double Am2m3 = M0 > 0 ? M_PI * pow(abs(6 / (M_PI * rhoSoot) * M1 / M0), 2.0 / 3) * abs(M0) : 0;

    double G0 = 0;
    double G1 = kGrw * Am2m3;

    if (out) {
        *out << "Am2m3: " << Am2m3 << endl;
        *out << "G0: " << G0 << endl;
        *out << "G1: " << G1 << endl;
        *out << endl;
    }

    //---------- oxidation terms

    double X0 = 0;
    double X1 = -kOxi * Am2m3;

    if (out) {
        *out << "X0: " << X0 << endl;
        *out << "X1: " << X1 << endl;
        *out << endl;
    }

    //---------- coagulation terms

    double C0 = -0.5 * coag * weights.at(0) * weights.at(0);
    double C1 = 0;

    if (out) {
        *out << "C0: " << C0 << endl;
        *out << "C1: " << C1 << endl;
        *out << endl;
    }

    //---------- combine to make soot source terms

    vector<double> sootSourceTerms = {(N0 + Cnd0 + G0 + X0 + C0) / state.rhoGas,
									  (N1 + Cnd1 + G1 + X1 + C1) / state.rhoGas};

    if (out) {
        *out << "Soot Source Terms (" << sootSourceTerms.size() << ")" << endl;
        for (size_t i = 0; i < sootSourceTerms.size(); i++)
            *out << i << ": " << sootSourceTerms.at(i) << endl;
        *out << endl;
    }

    //---------- get gas source terms

    map<gasSp, double> nucGas = nuc->getNucleationGasRates(state, N1).gasSourceTerms;
    map<gasSp, double> grwGas = grw->getGrowthGasRates(state, G1).gasSourceTerms;
    map<gasSp, double> oxiGas = oxi->getOxidationGasRates(state, X1).gasSourceTerms;
    // coagulation does not contribute to gas sources/sinks

    for (auto const& x : sourceTerms->gasSourceTerms) {

        gasSp sp = x.first;

        if (sp != gasSp::C)
            sourceTerms->gasSourceTerms.at(sp) = nucGas.at(sp) + grwGas.at(sp) + oxiGas.at(sp);
    }

    // TODO generalize PAH source terms


//    map<size_t, double> PAHSourceTerms = SootChemistry::getPAHSourceTerms(state, massRateRatios, N1, 0, X1, 0);

//    if (out) {
//        *out << "Gas Source Terms (" << gasSourceTerms.size() << ")" << endl;
//        for (const auto& [g, t] : gasSourceTerms)
//            *out << (int) g << ": " << t << endl;
//        *out << "PAH Source Terms (" << PAHSourceTerms.size() << ")" << endl;
//        for (const auto& [s, t] : PAHSourceTerms)
//            *out << s << ": " << t << endl;
//        *out << endl;
//    }
}

void psdModel_MONO::checkState(const state& state) const {
    if (state.sootVar.size() < 2)
        throw runtime_error("MONO soot model requires 2 soot moments");
    if (state.sootVar.size() > 2)
        cerr << "MONO soot model requires 2 soot moments, got " << state.sootVar.size() << endl;
}
