#include "SootModel_LOGN.h"

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
                               unique_ptr<OxidationModel> oxidationModel) : SootModel_Base(move(coagulationModel),
                                                                                           move(growthModel),
                                                                                           move(nucleationModel),
                                                                                           move(oxidationModel)) {
}
SourceTerms SootModel_LOGN::getSourceTerms(InputState& state) const {
    // TODO implement
    return SourceTerms();
}
