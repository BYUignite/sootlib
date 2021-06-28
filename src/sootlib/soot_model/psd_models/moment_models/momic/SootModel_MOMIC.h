#ifndef SOOTMODEL_MOMIC_H
#define SOOTMODEL_MOMIC_H

#include "sootlib/soot_model/PSDModel.h"
#include "sootlib/soot_model/SootChemistry.h"

namespace soot {
class SootModel_MOMIC : public PSDModel {
public:
    explicit SootModel_MOMIC(const SootChemistry& sootChemistry);
    ~SootModel_MOMIC() override = default;

private:
    SootChemistry sootChemistry;

    [[nodiscard]] SourceTerms getSourceTermsImplementation(State& state, std::ostream* out) const override;

    void checkState(const State& state) const override;

    // helper functions specific to this PSD
    [[nodiscard]] static size_t downselectIfNeeded(std::vector<double>& M);
    [[nodiscard]] static double f_grid(int x, int y, const std::vector<double>& M);
    [[nodiscard]] static double MOMICCoagulationRate(const State& state, size_t r);
    [[nodiscard]] static double lagrangeInterp(double x_i, const std::vector<double>& x, const std::vector<double>& y);
    [[nodiscard]] static double MOMIC(double p, const std::vector<double>& M);
};
}

#endif //SOOTMODEL_MOMIC_H
