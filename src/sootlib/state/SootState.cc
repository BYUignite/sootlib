#include "SootState.h"

using namespace std;
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
void SootState::printInfo(ostream& out) const {
    SectionalState::printInfo(out);
    MomentState::printInfo(out);

    out << " === [SootState] ===" << endl;
    out << "Rho Soot: " << rhoSoot << endl;
    out << "Dimer (cached): " << dimer << endl;
    out << "bCoag: " << bCoag << endl;
    out << "epsC: " << epsC << endl;
    out << "sootDf: " << sootDf << endl;
    out << endl;
}
