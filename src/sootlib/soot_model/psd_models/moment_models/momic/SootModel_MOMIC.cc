#include "SootModel_MOMIC.h"
#include "sootlib/soot_model/static.h"
#include "sootlib/soot_model/soot_chemistry/coagulation_model/CoagulationModel_MOMIC.h"

using namespace std;
using namespace soot;

SootModel_MOMIC* SootModel_MOMIC::getInstance(unique_ptr<CoagulationModel> coagulationModel,
                                              unique_ptr<GrowthModel> growthModel,
                                              unique_ptr<NucleationModel> nucleationModel,
                                              unique_ptr<OxidationModel> oxidationModel) {
    return new SootModel_MOMIC(move(coagulationModel),
                               move(growthModel),
                               move(nucleationModel),
                               move(oxidationModel));
}
SootModel_MOMIC::SootModel_MOMIC(unique_ptr<CoagulationModel> coagulationModel,
                                 unique_ptr<GrowthModel> growthModel,
                                 unique_ptr<NucleationModel> nucleationModel,
                                 unique_ptr<OxidationModel> oxidationModel) : SootChemistry(move(coagulationModel),
                                                                                            move(growthModel),
                                                                                            move(nucleationModel),
                                                                                            move(oxidationModel)) {
}
SourceTerms SootModel_MOMIC::getSourceTerms(State& state) const {
    const size_t N = downselectIfNeeded(state.getMoments());
    MassRateRatios massRateRatios;

    // FIXME it looks like these guys are trying to trigger optional parts of the supporting psd_models with negative values
    // this does not work well with what I have set up now :( there needs to be some explicit arguments for that
    const double Jnuc = nucleationModel->getNucleationRate(state, {}, {}, massRateRatios);
    const double Kgrw = growthModel->getGrowthRate(state, massRateRatios);
    const double Koxi = oxidationModel->getOxidationRate(state, massRateRatios);

    vector<double> Mnuc(state.getNumMoments(), 0);

    double m_nuc = state.getCMin() * MW_C / Na;
    for (size_t i = 0; i < N; i++)
        Mnuc.at(i) = pow(m_nuc, i) * Jnuc;

    vector<double> Mcnd(state.getNumMoments(), 0);

    CoagulationModel_MOMIC coag = CoagulationModel_MOMIC();
    if (nucleationModel->getMechanism() == NucleationMechanism::PAH) {
        for (size_t i = 1; i < N; i++)
            Mcnd.at(i) = coag.getCoagulationRate(state, (int) i) * state.getDimer() * state.getMDimer() * (double) i;
    }

    vector<double> Mgrw(state.getNumMoments(), 0);

    const double Acoef = M_PI * pow(abs(6 / M_PI / state.getRhoSoot()), 2.0 / 3);
    for (size_t i = 1; i < N; i++)
        Mgrw.at(i) = Kgrw * Acoef * (double) i * MOMIC((double) i - 1.0 / 3, state.getMomentsConst());

    vector<double> Moxi(state.getNumMoments(), 0);

    for (size_t i = 1; i < N; i++)
        Moxi.at(i) = Koxi * Acoef * (double) i * MOMIC((double) i - 1.0 / 3, state.getMomentsConst());

    vector<double> Mcoa(state.getNumMoments(), 0);

    if (coagulationModel->getMechanism() != CoagulationMechanism::NONE) {
        for (size_t i = 0; i < N; i++)
            Mcoa.at(i) = coag.getCoagulationRate(state, (int) i);
    }

    vector<double> sootSourceTerms(state.getNumMoments(), 0);
    for (size_t i = 0; i < state.getNumMoments(); i++)
        sootSourceTerms.at(i) = Mnuc.at(i) + Mcnd.at(i) + Mgrw.at(i) + Moxi.at(i) + Mcoa.at(i);

    //---------- get gas source terms

    map<GasSpecies, double> gasSourceTerms;
    map<size_t, double> PAHSourceTerms;

    // Nucleation
    for (auto it = massRateRatios.nucCond().gasSpeciesBegin(); it != massRateRatios.nucCond().gasSpeciesEnd(); it++)
        gasSourceTerms[it->first] += Mnuc.at(1) * it->second / state.getRhoGas();
    for (auto it = massRateRatios.nucCond().PAHBegin(); it != massRateRatios.nucCond().PAHEnd(); it++)
        PAHSourceTerms[it->first] += Mnuc.at(1) * it->second / state.getRhoGas();

    // Growth
    for (auto it = massRateRatios.groOxi().gasSpeciesBegin(); it != massRateRatios.groOxi().gasSpeciesEnd(); it++)
        gasSourceTerms[it->first] += Mgrw.at(1) * it->second / state.getRhoGas();

    // Oxidation
    for (auto it = massRateRatios.groOxi().gasSpeciesBegin(); it != massRateRatios.groOxi().gasSpeciesEnd(); it++)
        gasSourceTerms[it->first] += Moxi.at(1) * it->second / state.getRhoGas();
    for (auto it = massRateRatios.groOxi().PAHBegin(); it != massRateRatios.groOxi().PAHEnd(); it++)
        PAHSourceTerms[it->first] += Moxi.at(1) * it->second / state.getRhoGas();

    // PAH condensation
    for (auto it = massRateRatios.groOxi().gasSpeciesBegin(); it != massRateRatios.groOxi().gasSpeciesEnd(); it++)
        gasSourceTerms[it->first] += Mcnd.at(1) * it->second / state.getRhoGas();
    for (auto it = massRateRatios.nucCond().PAHBegin(); it != massRateRatios.nucCond().PAHEnd(); it++)
        PAHSourceTerms[it->first] += Mcnd.at(1) * it->second / state.getRhoGas();

    // Coagulation - n/a

    return SourceTerms(sootSourceTerms, gasSourceTerms, PAHSourceTerms);
}
