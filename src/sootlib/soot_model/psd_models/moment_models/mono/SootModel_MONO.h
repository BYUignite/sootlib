#ifndef SOOTMODEL_MONO_H
#define SOOTMODEL_MONO_H

#include "sootlib/soot_model/PSDModel.h"
#include "sootlib/soot_model/SootChemistry.h"

namespace soot {
class SootModel_MONO : public PSDModel {
public:
    explicit SootModel_MONO(const SootChemistry& sootChemistry);
    ~SootModel_MONO() override = default;

private:
    SootChemistry sootChemistry;

    [[nodiscard]] SourceTerms getSourceTermsImplementation(State& state, std::ostream* out) const override;
    void checkState(const State& state) const override;

    // helper functions specific to this PSD
};
}

#endif //SOOTMODEL_MONO_H
