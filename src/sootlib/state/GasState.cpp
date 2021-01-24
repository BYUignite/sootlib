#include "GasState.h"
double soot::GasState::getT() const
{
	return T;
}
void soot::GasState::setT(double t)
{
	T = t;
}
double soot::GasState::getP() const
{
	return P;
}
void soot::GasState::setP(double p)
{
	P = p;
}
double soot::GasState::getRho() const
{
	return rho;
}
void soot::GasState::setRho(double rho)
{
	GasState::rho = rho;
}
double soot::GasState::getMw() const
{
	return MW;
}
void soot::GasState::setMw(double mw)
{
	MW = mw;
}
double soot::GasState::getMu() const
{
	return mu;
}
void soot::GasState::setMu(double mu)
{
	GasState::mu = mu;
}
const soot::GasComponent& soot::GasState::getC2H2() const
{
	return C2H2;
}
void soot::GasState::setC2H2(const soot::GasComponent& c2H2)
{
	C2H2 = c2H2;
}
const soot::GasComponent& soot::GasState::getO2() const
{
	return O2;
}
void soot::GasState::setO2(const soot::GasComponent& o2)
{
	O2 = o2;
}
const soot::GasComponent& soot::GasState::getH() const
{
	return H;
}
void soot::GasState::setH(const soot::GasComponent& h)
{
	H = h;
}
const soot::GasComponent& soot::GasState::getH2() const
{
	return H2;
}
void soot::GasState::setH2(const soot::GasComponent& h2)
{
	H2 = h2;
}
const soot::GasComponent& soot::GasState::getOH() const
{
	return OH;
}
void soot::GasState::setOH(const soot::GasComponent& oh)
{
	OH = oh;
}
const soot::GasComponent& soot::GasState::getH2O() const
{
	return H2O;
}
void soot::GasState::setH2O(const soot::GasComponent& h2O)
{
	H2O = h2O;
}
const soot::GasComponent& soot::GasState::getCO() const
{
	return CO;
}
void soot::GasState::setCO(const soot::GasComponent& co)
{
	CO = co;
}
const soot::GasComponent& soot::GasState::getElementalC() const
{
	return elementalC;
}
void soot::GasState::setElementalC(const soot::GasComponent& elementalC)
{
	GasState::elementalC = elementalC;
}
const soot::GasComponent& soot::GasState::getElementalH() const
{
	return elementalH;
}
void soot::GasState::setElementalH(const soot::GasComponent& elementalH)
{
	GasState::elementalH = elementalH;
}
soot::GasComponent& soot::GasState::PAH(size_t numC)
{
	return PAHs[numC];
}
