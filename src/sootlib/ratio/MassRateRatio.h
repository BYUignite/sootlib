/**
 * Josh Bedwell - June 2021
 *
 * This MassRateRatio system is not good and should be replaced - Victoria Stevens has at least a prototype of a replacement
 */

#ifndef MASSRATERATIO_H
#define MASSRATERATIO_H

#include <map>

#include "sootlib/constants.h"

namespace soot {
/**
 * Stores the mass rate ratios of a set of gas species and PAH species
 */
class MassRateRatio {
public:
    /**
     * Gets a reference to a gasSpeciesRatio
     *
     * @param species the gas species requried
     * @return mass rate ratio for that species
     */
    double& gasSpeciesRatio(GasSpecies species) {
        if (gasSpeciesRatios.count(species) == 0)
            gasSpeciesRatios[species] = 0;
        return gasSpeciesRatios[species];
    }
    /**
     * Gets a reference to a PAHSpeciesRatio
     *
     * @param n the PAH species required
     * @return mass rate ratio for that species
     */
    double& PAHSpeciesRatio(size_t n) {
        if (PAHRatios.count(n) == 0)
            PAHRatios[n] = 0;
        return PAHRatios[n];
    }

    /**
     * Get a beginning iterator for the gasSpeciesRatios if you need to iterate through them
     *
     * @return gasSpeciesRatio iterator at begin position
     */
    [[nodiscard]] std::map<GasSpecies, double>::const_iterator gasSpeciesBegin() const {
        return gasSpeciesRatios.begin();
    }
    /**
     * Get an end iterator for the gasSpeciesRatios if you need to iterate through them
     *
     * @return gasSpeciesRatio iterator at the end position
     */
    [[nodiscard]] std::map<size_t, double>::const_iterator PAHBegin() const {
        return PAHRatios.begin();
    }
    /**
     * Get a beginning iterator for the PAHRatios if you need to iterate through them
     *
     * @return PAHRatio iterator at begin position
     */
    [[nodiscard]] std::map<GasSpecies, double>::const_iterator gasSpeciesEnd() const {
        return gasSpeciesRatios.end();
    }
    /**
     * Get an end iterator for the PAHRatios if you need to iterate through them
     *
     * @return PAHRatio iterator at the end position
     */
    [[nodiscard]] std::map<size_t, double>::const_iterator PAHEnd() const {
        return PAHRatios.end();
    }

private:
    /**
     * A map of the mass rate ratio of each gas species
     */
    std::map<GasSpecies, double> gasSpeciesRatios;
    /**
     * A map of the mass rate ratio of each PAH species
     */
    std::map<size_t, double> PAHRatios;
};
}

#endif //MASSRATERATIO_H
