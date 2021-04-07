#ifndef NUCLEATIONMODEL_PAH_H
#define NUCLEATIONMODEL_PAH_H

#include "NucleationModel.h"

namespace soot {
class NucleationModel_PAH : public NucleationModel {
public:
    [[nodiscard]] double getNucleationRate(State& state,
                                           const std::vector<double>& particleSizes,
                                           const std::vector<double>& particleWeights,
                                           MassRateRatios& ratio) const override;
    [[nodiscard]] NucleationMechanism getMechanism() const override {
        return NucleationMechanism::PAH;
    }

    ~NucleationModel_PAH() override = default;
};
}

#endif //NUCLEATIONMODEL_PAH_H
