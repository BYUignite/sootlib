#ifndef BASESTATE_H
#define BASESTATE_H

#include "sootlib/constants.h"
#include "sootlib/ratio/MassRateRatios.h"
#include "sootlib/state/SootState.h"
#include "sootlib/state/GasState.h"

namespace soot {
class State : public SootState, public GasState {
public:
    [[nodiscard]] double getCMin();
    void setCMin(double CMin);
    [[nodiscard]] double getMDimer();
    [[nodiscard]] double getWDotD();

    void calculateMDimer(MassRateRatios* ratio = nullptr);

    void setT(double T) override;
    void setRhoSoot(double rhoSoot) override;
    void setPAHFrac(size_t n, double frac) override;

    void printInfo(std::ostream& out) const;

private:
    // according to some specs it looks like cMin is a constant and according to others it looks calculated
    double cMin = 100;
    double mDimer = 0;
    double wdotD = 0;

    bool mDimerValid = true;

};
}

#endif //BASESTATE_H
