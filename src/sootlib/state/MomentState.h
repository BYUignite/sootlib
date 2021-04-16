#ifndef MOMENTSTATE_H_
#define MOMENTSTATE_H_

#include <vector>

namespace soot {
class MomentState {
public:
    [[nodiscard]] size_t getNumMoments() const;
    void resetMoments(size_t numMoments);
    [[nodiscard]] double getMoment(size_t i) const;
    void setMoment(size_t i, double value);
    std::vector<double>& getMoments();
    [[nodiscard]] const std::vector<double>& getMomentsConst() const;

protected:
    std::vector<double> moments;
};
}

#endif //MOMENTSTATE_H_
