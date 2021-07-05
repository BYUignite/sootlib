#ifndef NUCLEATIONMODEL_LIN_H
#define NUCLEATIONMODEL_LIN_H

#include "nucleationModel.h"

namespace soot {
class NucleationModel_LIN : public nucleationModel {
public:
    [[nodiscard]] double getNucleationRate(State& state,
                                           const std::vector<double>& particleSizes,
                                           const std::vector<double>& particleWeights,
                                           MassRateRatios& ratio) const override;
    [[nodiscard]] NucleationMechanism getMechanism() const override {
        return NucleationMechanism::LIN;
    }

    ~NucleationModel_LIN() override = default;
};
}

#endif //NUCLEATIONMODEL_LIN_H
