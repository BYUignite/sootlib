#ifndef NUCLEATIONMODEL_NONE_H
#define NUCLEATIONMODEL_NONE_H

#include "nucleationModel.h"

namespace soot {
class NucleationModel_NONE : public nucleationModel {
public:
    [[nodiscard]] double getNucleationRate(State& state,
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
