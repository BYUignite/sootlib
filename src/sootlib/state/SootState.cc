#include "SootState.h"

using namespace soot;

double SootState::getRhoSoot() const {
    return rhoSoot;
}
void SootState::setRhoSoot(double rhoSoot) {
    SootState::rhoSoot = rhoSoot;
}
double SootState::getDimer() const {
    return dimer;
}
void SootState::setDimer(double dimer) {
    SootState::dimer = dimer;
}
double SootState::getBCoag() const {
    return bCoag;
}
void SootState::setBCoag(double bCoag) {
    SootState::bCoag = bCoag;
}
double SootState::getEpsC() const {
    return epsC;
}
void SootState::setEpsC(double epsC) {
    SootState::epsC = epsC;
}
double SootState::getSootDf() const {
    return sootDf;
}
void SootState::setSootDf(double sootDf) {
    SootState::sootDf = sootDf;
}
