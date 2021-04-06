#ifndef SOOTMODEL_LOGN_H
#define SOOTMODEL_LOGN_H

#include "sootlib/soot_model/SootModel.h"
#include "sootlib/soot_model/SootModel_Base.h"

namespace soot {
class SootModel_LOGN : public SootModel, public SootModel_Base {
public:
    [[nodiscard]] static SootModel_LOGN* getInstance(std::unique_ptr<CoagulationModel> coagulationModel,
                                                     std::unique_ptr<GrowthModel> growthModel,
                                                     std::unique_ptr<NucleationModel> nucleationModel,
                                                     std::unique_ptr<OxidationModel> oxidationModel);

    [[nodiscard]] SourceTerms getSourceTerms(InputState& state) const override;

    ~SootModel_LOGN() override = default;

private:
    SootModel_LOGN(std::unique_ptr<CoagulationModel> coagulationModel,
                   std::unique_ptr<GrowthModel> growthModel,
                   std::unique_ptr<NucleationModel> nucleationModel,
                   std::unique_ptr<OxidationModel> oxidationModel);

    [[nodiscard]] double Mk_LOGN(double k, double M0, double M1, double M2) const;
};
}

#endif //SOOTMODEL_LOGN_H
