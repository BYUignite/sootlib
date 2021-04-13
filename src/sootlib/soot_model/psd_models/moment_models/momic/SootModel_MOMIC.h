#ifndef SOOTMODEL_MOMIC_H
#define SOOTMODEL_MOMIC_H

#include "sootlib/soot_model/SootModel.h"
#include "sootlib/soot_model/SootChemistry.h"

namespace soot {
class SootModel_MOMIC : public SootModel, public SootChemistry {
public:
    [[nodiscard]] static SootModel_MOMIC* getInstance(std::unique_ptr<CoagulationModel> coagulationModel,
                                                      std::unique_ptr<GrowthModel> growthModel,
                                                      std::unique_ptr<NucleationModel> nucleationModel,
                                                      std::unique_ptr<OxidationModel> oxidationModel);

    [[nodiscard]] SourceTerms getSourceTerms(State& state) const override;

    ~SootModel_MOMIC() override = default;

private:
    SootModel_MOMIC(std::unique_ptr<CoagulationModel> coagulationModel,
                    std::unique_ptr<GrowthModel> growthModel,
                    std::unique_ptr<NucleationModel> nucleationModel,
                    std::unique_ptr<OxidationModel> oxidationModel);

    // helper functions specific to this PSD
};
}

#endif //SOOTMODEL_MOMIC_H
