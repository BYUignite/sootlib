#include "MomentState.h"

using namespace std;
using namespace soot;

MomentState::MomentState(size_t numMoments) {
    if (numMoments != 0)
        resetMoments(numMoments);
}
size_t MomentState::getNumMoments() const {
    return moments.size();
}
void MomentState::resetMoments(size_t numMoments) {
    moments = vector<double>(numMoments, 0);
}
double MomentState::getMoment(size_t i) const {
    return moments.at(i);
}
void MomentState::setMoment(size_t i, double value) {
    moments.at(i) = value;
}
