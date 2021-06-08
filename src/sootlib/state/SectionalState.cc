#include "SectionalState.h"

using namespace soot;
using namespace std;

size_t SectionalState::getNumSections() const {
    return sections.size();
}
void SectionalState::resetSections(size_t numSections) {
    sections = vector<double>(numSections, 0);
}
double SectionalState::getSection(size_t i) const {
    return sections.at(i);
}
void SectionalState::setSection(size_t i, double value) {
    sections.at(i) = value;
}
vector<double>& SectionalState::getSections() {
    return sections;
}
const vector<double>& SectionalState::getSectionsConst() const {
    return sections;
}
void SectionalState::printInfo(ostream& out) const {
    out << " === [SectionState] ===" << endl;
    out << "Sections (" << sections.size() << ")" << endl;
    for (size_t i = 0; i < sections.size(); i++)
        out << i << ": " << sections.at(i) << endl;
    out << endl;
}
void SectionalState::checkSize(size_t i) const {
    if (i > sections.size())
        throw range_error("Section " + to_string(i) + " out of bounds for state with " + to_string(sections.size()) + " sections");
}
