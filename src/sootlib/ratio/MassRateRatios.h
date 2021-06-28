/**
 * Josh Bedwell - June 2021
 *
 * This MassRateRatio system is not good and should be replaced - Victoria Stevens has at least a prototype of a replacement
 */

#ifndef MASSRATERATIOS_H_
#define MASSRATERATIOS_H_

#include "sootlib/ratio/MassRateRatio.h"

namespace soot {
/**
 * Simply holds a MassRateRatio for nucleation/condensation and one for growth/oxidation
 * These are the pairs they always seem to come in
 */
class MassRateRatios {
public:
    /**
     * Gets a reference to the nucleationCondensation MassRateRatio
     *
     * @return the nucleationCondensation MassRateRatio
     */
    MassRateRatio& nucCond() {
        return nucleationCondensation;
    }
    /**
     * Gets a reference to the growthOxidation MassRateRatio
     *
     * @return the growthOxidation MassRateRatio
     */
    MassRateRatio& groOxi() {
        return growthOxidation;
    }

private:
    /**
     * The MassRateRatio associated with nucleation and condensation chemistry
     */
    MassRateRatio nucleationCondensation;
    /**
     * The MassRateRatio associated with growth and oxidation chemistry
     */
    MassRateRatio growthOxidation;
};
}

#endif //MASSRATERATIOS_H_
