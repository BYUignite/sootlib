#ifndef MASSRATERATIOS_H_
#define MASSRATERATIOS_H_

#include "sootlib/MassRateRatio.h"

namespace soot {
class MassRateRatios {
public:
    MassRateRatio& nucCond() {
        return nucleationCondensation;
    }
    MassRateRatio& groOxi() {
        return growthOxidation;
    }

    void reset() {
        nucleationCondensation = MassRateRatio();
        growthOxidation = MassRateRatio();
    }

private:
    MassRateRatio nucleationCondensation;
    MassRateRatio growthOxidation;
};
}

#endif //MASSRATERATIOS_H_
