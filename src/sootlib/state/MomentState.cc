#include "MomentState.h"

using namespace soot;
using namespace std;

size_t MomentState::getNumMoments() const {
    return moments.size();
}
void MomentState::resetMoments(size_t numMoments) {
    moments = vector<double>(numMoments, 0);
}
double MomentState::getMoment(size_t i) const {
    checkSize(i);
    return moments.at(i);
}
void MomentState::setMoment(size_t i, double value) {
    checkSize(i);
    moments.at(i) = value;
}
vector<double>& MomentState::getMoments() {
    return moments;
}
const vector<double>& MomentState::getMomentsConst() const {
    return moments;
}
void MomentState::printInfo(ostream& out) const {
    out << " === [MomentState] ===" << endl;
    out << "Moments (" << moments.size() << ")" << endl;
    for (size_t i = 0; i < moments.size(); i++)
        out << i << ": " << moments.at(i) << endl;
    out << endl;
}
void MomentState::checkSize(size_t i) const {
    if (i >= moments.size())
        throw range_error("Moment " + to_string(i) + " out of bounds for state with " + to_string(moments.size()) + " moments");
}
