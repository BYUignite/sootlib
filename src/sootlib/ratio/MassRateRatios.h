#ifndef MASSRATERATIOS_H_
#define MASSRATERATIOS_H_

#include "sootlib/ratio/MassRateRatio.h"

namespace soot {
class MassRateRatios {
public:
    MassRateRatio& nucCond() {
        return nucleationCondensation;
    }
    MassRateRatio& groOxi() {
        return growthOxidation;
    }

private:
    MassRateRatio nucleationCondensation;
    MassRateRatio growthOxidation;
};
}

#endif //MASSRATERATIOS_H_
