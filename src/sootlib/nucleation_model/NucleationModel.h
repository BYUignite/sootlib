#ifndef NUCLEATIONMODEL_H
#define NUCLEATIONMODEL_H

#include <vector>

#include "sootlib/state/MomentState.h"
#include "sootlib/MassRateRatios.h"

namespace soot {
class NucleationModel {
public:
    [[nodiscard]] virtual double getNucleationRate(MomentState& state,
                                                   const std::vector<double>& particleSizes,
                                                   const std::vector<double>& particleWeights,
                                                   MassRateRatios& ratio) const = 0;
    [[nodiscard]] virtual NucleationMechanism getMechanism() const = 0;

    virtual ~NucleationModel() = default;
};
}

#endif //NUCLEATIONMODEL_H
