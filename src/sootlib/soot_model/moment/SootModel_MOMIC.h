#ifndef SOOTMODEL_MOMIC_H
#define SOOTMODEL_MOMIC_H

#include "sootlib/soot_model/moment/MomentSootModel.h"
#include "sootlib/MassRateRatio.h"
#include "sootlib/soot_model/SootModel_Base.h"

namespace soot {
class SootModel_MOMIC : public MomentSootModel, public SootModel_Base {
public:
    [[nodiscard]] static SootModel_MOMIC* getInstance(std::unique_ptr<CoagulationModel> coagulationModel,
                                                      std::unique_ptr<GrowthModel> growthModel,
                                                      std::unique_ptr<NucleationModel> nucleationModel,
                                                      std::unique_ptr<OxidationModel> oxidationModel);

    [[nodiscard]] SourceTerms getSourceTerms(MomentState& state) const override;

    ~SootModel_MOMIC() override = default;

private:
    SootModel_MOMIC(std::unique_ptr<CoagulationModel> coagulationModel,
                    std::unique_ptr<GrowthModel> growthModel,
                    std::unique_ptr<NucleationModel> nucleationModel,
                    std::unique_ptr<OxidationModel> oxidationModel);
};
}

#endif //SOOTMODEL_MOMIC_H
