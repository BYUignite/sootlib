#ifndef SOOTMODEL_SECT_H
#define SOOTMODEL_SECT_H

#include "sootlib/soot_model/PSDModel.h"
#include "sootlib/soot_model/SootChemistry.h"

namespace soot {
class SootModel_SECT : public PSDModel {
public:
    explicit SootModel_SECT(const SootChemistry& sootChemistry);
    ~SootModel_SECT() override = default;

private:
    SootChemistry sootChemistry;

    [[nodiscard]] SourceTerms getSourceTermsImplementation(State& state, std::ostream* out) const override;

    void checkState(const State& state) const override;

    // helper functions specific to this PSD
    [[nodiscard]] static std::vector<double> getDivision(double mass, double num, const std::vector<double>& absc);
};
}

#endif //SOOTMODEL_SECT_H
