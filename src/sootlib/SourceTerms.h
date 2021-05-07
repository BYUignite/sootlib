#ifndef SOURCETERMS_H
#define SOURCETERMS_H

#include <ostream>
#include <map>
#include <utility>
#include <vector>

#include "sootlib/constants.h"

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
    [[nodiscard]] size_t getNumPAHSourceTerms() {
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

    void printInfo(std::ostream& out) const {
    	out << " === [SourceTerms] ===" << std::endl;

    	out << "Soot Source Terms (" << sootSourceTerms.size() << ")" << std::endl;
    	for (size_t i = 0; i < sootSourceTerms.size(); i++)
    		out << i << ": " << sootSourceTerms.at(i) << std::endl;
    	out << std::endl;

    	out << "Gas Source Terms (" << gasSourceTerms.size() << ")" << std::endl;
    	for (const auto& [g, t] : gasSourceTerms)
    		out << "Gas " << (int) g << ": " << t << std::endl;
    	out << std::endl;

    	out << "PAH Source Terms (" << PAHSourceTerms.size() << ")" << std::endl;
    	for (const auto& [p, t] : PAHSourceTerms)
    		out << "PAH species " << p << ": " << t << std::endl;

    	out << std::endl;
    }

private:
    std::vector<double> sootSourceTerms;
    std::map<GasSpecies, double> gasSourceTerms;
    std::map<size_t, double> PAHSourceTerms;
};
}

#endif //SOURCETERMS_H
