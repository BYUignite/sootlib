#ifndef NUCLEATIONMODEL_LL_H
#define NUCLEATIONMODEL_LL_H

#include "nucleationModel.h"

namespace soot {
class NucleationModel_LL : public nucleationModel {
public:
    [[nodiscard]] double getNucleationRate(State& state,
                                           const std::vector<double>& particleSizes,
                                           const std::vector<double>& particleWeights,
                                           MassRateRatios& ratio) const override;
    [[nodiscard]] NucleationMechanism getMechanism() const override {
        return NucleationMechanism::LL;
    }

    ~NucleationModel_LL() override = default;
};
}

#endif //NUCLEATIONMODEL_LL_H
