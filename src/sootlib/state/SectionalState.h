#ifndef SECTIONALSTATE_H_
#define SECTIONALSTATE_H_

#include <vector>

namespace soot {
class SectionalState {
public:
    [[nodiscard]] size_t getNumSections() const;
    void resetSections(size_t numSections);
    [[nodiscard]] double getSection(size_t i) const;
    void setSection(size_t i, double value);
    std::vector<double>& getSections();
    [[nodiscard]] const std::vector<double>& getSectionsConst() const;

protected:
    std::vector<double> sections;
};
}

#endif //SECTIONALSTATE_H_
