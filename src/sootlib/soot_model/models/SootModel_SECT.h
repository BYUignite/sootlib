#ifndef SOOTMODEL_SECT_H
#define SOOTMODEL_SECT_H

#include "sootlib/soot_model/SootModel.h"
#include "sootlib/soot_model/SootModel_Base.h"

namespace soot {
class SootModel_SECT : public SootModel, public SootModel_Base {
public:
    [[nodiscard]] static SootModel_SECT* getInstance(std::unique_ptr<CoagulationModel> coagulationModel,
                                                     std::unique_ptr<GrowthModel> growthModel,
                                                     std::unique_ptr<NucleationModel> nucleationModel,
                                                     std::unique_ptr<OxidationModel> oxidationModel);

    [[nodiscard]] SourceTerms getSourceTerms(InputState& state) const override;

    ~SootModel_SECT() override = default;

private:
    SootModel_SECT(std::unique_ptr<CoagulationModel> coagulationModel,
                   std::unique_ptr<GrowthModel> growthModel,
                   std::unique_ptr<NucleationModel> nucleationModel,
                   std::unique_ptr<OxidationModel> oxidationModel);
};
}

#endif //SOOTMODEL_SECT_H
