#ifndef MOMENTSTATE_H
#define MOMENTSTATE_H

#include <vector>

#include "sootlib/state/BaseState.h"

namespace soot {
class MomentState : public BaseState {
public:
    explicit MomentState(size_t numMoments = 0);

    [[nodiscard]] size_t getNumMoments() const;
    void resetMoments(size_t numMoments);
    [[nodiscard]] double getMoment(size_t i) const;
    void setMoment(size_t i, double value);

private:
    std::vector<double> moments;
};
}

#endif //MOMENTSTATE_H
