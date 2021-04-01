#ifndef NUCLEATIONMODEL_NONE_H
#define NUCLEATIONMODEL_NONE_H

#include "sootlib/nucleation_model/NucleationModel.h"

namespace soot {
class NucleationModel_NONE : public NucleationModel {
public:
    [[nodiscard]] double getNucleationRate(InputState& state,
                                           const std::vector<double>& particleSizes,
                                           const std::vector<double>& particleWeights,
                                           MassRateRatios& ratio) const override {
        return 0;
    }
    [[nodiscard]] NucleationMechanism getMechanism() const override {
        return NucleationMechanism::NONE;
    }

    ~NucleationModel_NONE() override = default;
};
}

#endif //NUCLEATIONMODEL_NONE_H
