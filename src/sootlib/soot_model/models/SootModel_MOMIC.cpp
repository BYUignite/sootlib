#include "SootModel_MOMIC.h"
#include "sootlib/soot_model/static.h"

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
                                 unique_ptr<OxidationModel> oxidationModel) : SootModel_Base(move(coagulationModel),
                                                                                             move(growthModel),
                                                                                             move(nucleationModel),
                                                                                             move(oxidationModel)) {
}
SourceTerms SootModel_MOMIC::getSourceTerms(InputState& state) const {
    const size_t N = downselectIfNeeded(state.getMoments());
    MassRateRatios massRateRatios;

    // FIXME it looks like these guys are trying to trigger optional parts of the supporting models with negative values
    // this does not work well with what I have set up now :( there needs to be some explicit arguments for that
    const double Jnuc = nucleationModel->getNucleationRate(state, {}, {}, massRateRatios);
    const double Kgrw = growthModel->getGrowthRate(state, massRateRatios);
    const double Koxi = oxidationModel->getOxidationRate(state, massRateRatios);

    vector<double> Mnuc(state.getNumMoments(), 0);

    double m_nuc = state.getCMin() * MW_C / Na;
    for (size_t k = 0; k < N; k++)
        Mnuc.at(k) = pow(m_nuc, k) * Jnuc;

    vector<double> Mcnd(state.getNumMoments(), 0);

    if (nucleationModel->getMechanism() == NucleationMechanism::PAH) {
        for (size_t k = 1; k < N; k++) {
            // TODO add this
            // Mcnd.at(k) = getCoag(k);
            Mcnd.at(k) *= state.getDimer() * state.getMDimer() * k;
        }
    }

    return SourceTerms();
}
