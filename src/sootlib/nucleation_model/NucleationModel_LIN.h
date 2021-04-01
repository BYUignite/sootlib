#ifndef NUCLEATIONMODEL_LIN_H
#define NUCLEATIONMODEL_LIN_H

#include "sootlib/nucleation_model/NucleationModel.h"

namespace soot {
class NucleationModel_LIN : public NucleationModel {
public:
    [[nodiscard]] double getNucleationRate(InputState& state,
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
