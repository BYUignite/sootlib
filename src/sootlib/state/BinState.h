#ifndef BINSTATE_H
#define BINSTATE_H

#include <vector>

#include "sootlib/state/BaseState.h"

namespace soot {
class BinState : public BaseState {
public:
    explicit BinState(size_t numBins = 0);

    [[nodiscard]] size_t getNumBins() const;
    void resetBins(size_t numBins);
    [[nodiscard]] double getBin(size_t i) const;
    void setBin(size_t i, double value);

private:
    std::vector<double> bins;
};
}

#endif //BINSTATE_H
