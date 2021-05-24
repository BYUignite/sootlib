#ifndef SOOTMODEL_MONO_H
#define SOOTMODEL_MONO_H

#include "sootlib/soot_model/SootModel.h"
#include "sootlib/soot_model/SootChemistry.h"

namespace soot {
class SootModel_MONO : public SootModel, public SootChemistry {
public:
    [[nodiscard]] static SootModel_MONO* getInstance(std::unique_ptr<CoagulationModel> coagulationModel,
                                                     std::unique_ptr<GrowthModel> growthModel,
                                                     std::unique_ptr<NucleationModel> nucleationModel,
                                                     std::unique_ptr<OxidationModel> oxidationModel);

    ~SootModel_MONO() override = default;

private:
    [[nodiscard]] SourceTerms getSourceTermsImpl(State& state, std::ostream* out) const override;

    void checkState(const State& state) const override;

    SootModel_MONO(std::unique_ptr<CoagulationModel> coagulationModel,
                   std::unique_ptr<GrowthModel> growthModel,
                   std::unique_ptr<NucleationModel> nucleationModel,
                   std::unique_ptr<OxidationModel> oxidationModel);

    // helper functions specific to this PSD
};
}

#endif //SOOTMODEL_MONO_H
