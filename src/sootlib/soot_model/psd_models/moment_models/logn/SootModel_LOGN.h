#ifndef SOOTMODEL_LOGN_H
#define SOOTMODEL_LOGN_H

#include "sootlib/soot_model/SootModel.h"
#include "sootlib/soot_model/SootChemistry.h"

namespace soot {
class SootModel_LOGN : public SootModel, public SootChemistry {
public:
    [[nodiscard]] static SootModel_LOGN* getInstance(std::unique_ptr<CoagulationModel> coagulationModel,
                                                     std::unique_ptr<GrowthModel> growthModel,
                                                     std::unique_ptr<NucleationModel> nucleationModel,
                                                     std::unique_ptr<OxidationModel> oxidationModel);

    ~SootModel_LOGN() override = default;

private:
    [[nodiscard]] SourceTerms getSourceTermsImpl(State& state, std::ostream* out) const override;

    void checkState(const State& state) const override;

    SootModel_LOGN(std::unique_ptr<CoagulationModel> coagulationModel,
                   std::unique_ptr<GrowthModel> growthModel,
                   std::unique_ptr<NucleationModel> nucleationModel,
                   std::unique_ptr<OxidationModel> oxidationModel);

    // helper functions specific to this PSD
    [[nodiscard]] static double Mk(double k, double M0, double M1, double M2);
    [[nodiscard]] static double getKfm(const State& state);
    [[nodiscard]] static double getKc(const State& state);
    [[nodiscard]] static double getKcp(const State& state);
};
}

#endif //SOOTMODEL_LOGN_H
