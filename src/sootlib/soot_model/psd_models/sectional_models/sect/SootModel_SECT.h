#ifndef SOOTMODEL_SECT_H
#define SOOTMODEL_SECT_H

#include "sootlib/soot_model/SootModel.h"
#include "sootlib/soot_model/SootChemistry.h"

namespace soot {
class SootModel_SECT : public SootModel, public SootChemistry {
public:
    [[nodiscard]] static SootModel_SECT* getInstance(std::unique_ptr<CoagulationModel> coagulationModel,
                                                     std::unique_ptr<GrowthModel> growthModel,
                                                     std::unique_ptr<NucleationModel> nucleationModel,
                                                     std::unique_ptr<OxidationModel> oxidationModel);

    ~SootModel_SECT() override = default;

private:
    [[nodiscard]] SourceTerms getSourceTermsImpl(State& state, std::ostream* out) const override;

    SootModel_SECT(std::unique_ptr<CoagulationModel> coagulationModel,
                   std::unique_ptr<GrowthModel> growthModel,
                   std::unique_ptr<NucleationModel> nucleationModel,
                   std::unique_ptr<OxidationModel> oxidationModel);

    // helper functions specific to this PSD
    [[nodiscard]] static std::vector<double> getDivision(double mass, double num, const std::vector<double>& absc);
};
}

#endif //SOOTMODEL_SECT_H
