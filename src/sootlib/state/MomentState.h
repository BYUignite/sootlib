#ifndef MOMENTSTATE_H_
#define MOMENTSTATE_H_

#include <ostream>
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

    void printInfo(std::ostream& out) const;

protected:
    std::vector<double> moments;

private:
    void checkSize(size_t i) const;
};
}

#endif //MOMENTSTATE_H_
