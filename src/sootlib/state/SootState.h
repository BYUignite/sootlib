#ifndef SOOTSTATE_H_
#define SOOTSTATE_H_

#include "sootlib/state/SectionalState.h"
#include "sootlib/state/MomentState.h"

namespace soot {
class SootState : public SectionalState, public MomentState {
public:
    [[nodiscard]] double getRhoSoot() const;
    void setRhoSoot(double rhoSoot);
    [[nodiscard]] double getDimer() const;
    void setDimer(double dimer);
    [[nodiscard]] double getBCoag() const;
    void setBCoag(double bCoag);
    [[nodiscard]] double getEpsC() const;
    void setEpsC(double epsC);
    [[nodiscard]] double getSootDf() const;
    void setSootDf(double sootDf);

protected:
    double rhoSoot = 1850;
    double dimer = 0;
    // FIXME this variable isn't used
    double bCoag = 0.8536;
    // FIXME this variable isn't used
    double epsC = 2.2;
    // FIXME this variable isn't used
    double sootDf = 1.8;
};
}

#endif //SOOTSTATE_H_
