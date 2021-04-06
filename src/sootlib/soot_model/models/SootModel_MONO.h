#ifndef SOOTMODEL_MONO_H
#define SOOTMODEL_MONO_H

#include "sootlib/soot_model/SootModel.h"
#include "sootlib/soot_model/SootModel_Base.h"

namespace soot {

class SootModel_MONO : public SootModel, public SootModel_Base {

public:
    [[nodiscard]] static SootModel_MONO* getInstance(std::unique_ptr<CoagulationModel> coagulationModel,
                                                     std::unique_ptr<GrowthModel> growthModel,
                                                     std::unique_ptr<NucleationModel> nucleationModel,
                                                     std::unique_ptr<OxidationModel> oxidationModel);

    [[nodiscard]] SourceTerms getSourceTerms(InputState& state) const override;

    ~SootModel_MONO() override = default;

private:

    SootModel_MONO(std::unique_ptr<CoagulationModel> coagulationModel,
                   std::unique_ptr<GrowthModel> growthModel,
                   std::unique_ptr<NucleationModel> nucleationModel,
                   std::unique_ptr<OxidationModel> oxidationModel);

};
}

#endif //SOOTMODEL_MONO_H