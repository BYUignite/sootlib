#ifndef NUCLEATIONMODEL_H
#define NUCLEATIONMODEL_H

#include <vector>

#include "src/state.h"

namespace soot {
class nucleationModel {
public:
    [[nodiscard]] virtual double getNucleationRate(state& state,
                                                   const std::vector<double>& particleSizes,
                                                   const std::vector<double>& particleWeights,
                                                   MassRateRatios& ratio) const = 0;
    [[nodiscard]] virtual nucleationMechanism getMechanism() const = 0;

    virtual ~nucleationModel() = default;
};
}

#endif //NUCLEATIONMODEL_H
