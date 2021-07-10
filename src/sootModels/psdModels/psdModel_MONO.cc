#include "psdModel_MONO.h"

using namespace std;
using namespace soot;

//TODO remove sootChemistry, replace appropriately
psdModel_MONO::psdModel_MONO(size_t n) {

    if (n != 2) {
        // issue warning message, notify user that MONO will default to 2 moments
    }
    this->nMom = 2;

}

////////////////////////////////////////////////////////////////////////////////
/** getSourceTermsImplementation function
 *  
 *      Calculates soot source terms using monodispersed PSD model (MONO).
 *      Returns soot, gas, and PAH source terms (where applicable). 
 *
 *      @param  state    \input gas/soot state (?)
 *
 */

sourceTermStruct psdModel_MONO::getSourceTermsImplementation(state& state, std::ostream* out) const {

    if (out) {
        *out << " === [SootModel MONO] ===" << endl;
        *out << endl;
    }

    vector<double> weights = {0};
    vector<double> abscissas = {0};

    //---------- get moments

    const double M0 = state.getMoment(0);
    const double M1 = state.getMoment(1);

    //---------- set weights and abscissas

    if (M0 > 0) {
        weights.at(0) = M0;
        abscissas.at(0) = M1 / M0;
    }

    //---------- get chemical rates

//    const double jNuc = sootModel.nucleationModel->getNucleationRate(state, abscissas, weights, massRateRatios);
//    const double kGrw = sootModel.growthModel->getGrowthRate(state, massRateRatios);
//    const double kOxi = sootModel.oxidationModel->getOxidationRate(state, massRateRatios);
//    const double coag = sootModel.coagulationModel->getCoagulationRate(state, abscissas.at(0), abscissas.at(0));
    const double jNuc = sootModel.nuc->getNucleationRate(state, abscissas, weights);
    const double kGrw = sootModel.grw->getGrowthRate(state);
    const double kOxi = sootModel.oxi->getOxidationRate(state);
    const double coag = sootModel.coa->getCoagulationRate(state, abscissas.at(0), abscissas.at(0));

    if (out) {
        *out << "jNuc: " << jNuc << endl;
        *out << "kGrw: " << kGrw << endl;
        *out << "kOxi: " << kOxi << endl;
        *out << "coag: " << coag << endl;
        *out << endl;
    }

    //---------- nucleation terms

    const double N0 = jNuc;
    const double N1 = jNuc * cMin * MW_C / Na;

    if (out) {
        *out << "N0: " << N0 << endl;
        *out << "N1: " << N1 << endl;
        *out << endl;
    }

    //---------- PAH condensation terms

    const double Cnd0 = 0;
    const double Cnd1 = sootChemistry.nucleationModel->getMechanism() == nucleationMech::PAH ? state.getDimer() * state.getMDimer() * sootChemistry.coagulationModel->getCoagulationRate(state, state.getMDimer(), abscissas.at(0)) * weights.at(0) : 0;

    if (out) {
        *out << "Cnd0: " << Cnd0 << endl;
        *out << "Cnd1: " << Cnd1 << endl;
        *out << endl;
    }

    //---------- growth terms

    const double Am2m3 = M0 > 0 ? M_PI * pow(abs(6 / (M_PI * state.getRhoSoot()) * M1 / M0), 2.0 / 3) * abs(M0) : 0;

    const double G0 = 0;
    const double G1 = kGrw * Am2m3;

    if (out) {
        *out << "Am2m3: " << Am2m3 << endl;
        *out << "G0: " << G0 << endl;
        *out << "G1: " << G1 << endl;
        *out << endl;
    }

    //---------- oxidation terms

    const double X0 = 0;
    const double X1 = -kOxi * Am2m3;

    if (out) {
        *out << "X0: " << X0 << endl;
        *out << "X1: " << X1 << endl;
        *out << endl;
    }

    //---------- coagulation terms

    const double C0 = -0.5 * coag * weights.at(0) * weights.at(0);
    const double C1 = 0;

    if (out) {
        *out << "C0: " << C0 << endl;
        *out << "C1: " << C1 << endl;
        *out << endl;
    }

    //---------- combine to make soot source terms

    vector<double> sootSourceTerms = {(N0 + Cnd0 + G0 + X0 + C0) / state.getRhoGas(),
									  (N1 + Cnd1 + G1 + X1 + C1) / state.getRhoGas()};

    if (out) {
        *out << "Soot Source Terms (" << sootSourceTerms.size() << ")" << endl;
        for (size_t i = 0; i < sootSourceTerms.size(); i++)
            *out << i << ": " << sootSourceTerms.at(i) << endl;
        *out << endl;
    }

    //---------- get gas source terms

    map<gasSp, double> gasSourceTerms = SootChemistry::getGasSourceTerms(state, massRateRatios, N1, G1, X1, 0);
    map<size_t, double> PAHSourceTerms = SootChemistry::getPAHSourceTerms(state, massRateRatios, N1, 0, X1, 0);

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
void psdModel_MONO::checkState(const state& state) const {
    if (state.getNumMoments() < 2)
        throw runtime_error("MONO soot model requires 2 soot moments");
    if (state.getNumMoments() > 2)
        cerr << "MONO soot model requires 2 soot moments, got " << state.getNumMoments() << endl;
}
