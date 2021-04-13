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
    static size_t downselectIfNeeded(std::vector<double>& M);
    static double f_grid(int x, int y, const std::vector<double>& M);
    static double MOMICCoagulationRate(const State& state, int r);
    static double lagrangeInterp(double x_i, const std::vector<double>& x, const std::vector<double>& y);
    static double MOMIC(double p, const std::vector<double>& M);
};
}

#endif //SOOTMODEL_MOMIC_H
