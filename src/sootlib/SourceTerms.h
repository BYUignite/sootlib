#ifndef SOURCETERMS_H
#define SOURCETERMS_H

#include <map>
#include <utility>
#include <vector>

#include "sootlib/static.h"

namespace soot {
class SourceTerms {
public:
    /* Constructors */

    SourceTerms() = default;

    explicit SourceTerms(std::vector<double> sootSourceTerms,
                         std::map<GasSpecies, double> gasSourceTerms,
                         std::map<size_t, double> PAHSourceTerms) {
        this->sootSourceTerms = std::move(sootSourceTerms);
        this->gasSourceTerms = std::move(gasSourceTerms);
        this->PAHSourceTerms = std::move(PAHSourceTerms);
    }

    /* Getters and setters */

    [[nodiscard]] double getSootSourceTerm(size_t i) const {
        return sootSourceTerms.at(i);
    }
    void setSootSourceTerm(size_t i, double value) {
        sootSourceTerms.at(i) = value;
    }
    [[nodiscard]] size_t getNumSootSourceTerms() const {
        return sootSourceTerms.size();
    }

    [[nodiscard]] double getGasSourceTerm(GasSpecies species, double def = 0) {
        if (gasSourceTerms.count(species) == 0)
            return def;
        return gasSourceTerms.at(species);
    }
    void setGasSourceTerm(GasSpecies species, double value) {
        gasSourceTerms[species] = value;
    }
    [[nodiscard]] size_t getNumGasSourceTerms() const {
        return gasSourceTerms.size();
    }

    [[nodiscard]] double getPAHSourceTerm(size_t n, double def = 0) {
        if (PAHSourceTerms.count(n) == 0)
            return def;
        return PAHSourceTerms.at(n);
    }
    void setPAHSourceTerm(size_t n, double value) {
        PAHSourceTerms[n] = value;
    }
    [[nodiscard]] double getNumPAHSourceTerms() {
        return PAHSourceTerms.size();
    }

    /* Const iterators */

    [[nodiscard]] std::vector<double>::const_iterator sootTermsBegin() const {
        return sootSourceTerms.begin();
    }
    [[nodiscard]] std::vector<double>::const_iterator sootTermsEnd() const {
        return sootSourceTerms.end();
    }
    [[nodiscard]] std::map<GasSpecies, double>::const_iterator gasTermsBegin() const {
        return gasSourceTerms.begin();
    }
    [[nodiscard]] std::map<GasSpecies, double>::const_iterator gasTermsEnd() const {
        return gasSourceTerms.end();
    }
    [[nodiscard]] std::map<size_t, double>::const_iterator PAHTermsBegin() const {
        return PAHSourceTerms.begin();
    }
    [[nodiscard]] std::map<size_t, double>::const_iterator PAHTermsEnd() const {
        return PAHSourceTerms.end();
    }

private:
    std::vector<double> sootSourceTerms;
    std::map<GasSpecies, double> gasSourceTerms;
    std::map<size_t, double> PAHSourceTerms;
};
}

#endif //SOURCETERMS_H
