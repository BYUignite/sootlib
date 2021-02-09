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
soot::GasComponent& soot::GasState::PAH(size_t numC)
{
	return PAHs[numC];
}
double soot::GasState::getC2H2Frac() const
{
	return C2H2_frac;
}
void soot::GasState::setC2H2Frac(double c2H2Frac)
{
	C2H2_frac = c2H2Frac;
}
double soot::GasState::getO2Frac() const
{
	return O2_frac;
}
void soot::GasState::setO2Frac(double o2Frac)
{
	O2_frac = o2Frac;
}
double soot::GasState::getHFrac() const
{
	return H_frac;
}
void soot::GasState::setHFrac(double hFrac)
{
	H_frac = hFrac;
}
double soot::GasState::getH2Frac() const
{
	return H2_frac;
}
void soot::GasState::setH2Frac(double h2Frac)
{
	H2_frac = h2Frac;
}
double soot::GasState::getOhFrac() const
{
	return OH_frac;
}
void soot::GasState::setOhFrac(double ohFrac)
{
	OH_frac = ohFrac;
}
double soot::GasState::getH2OFrac() const
{
	return H2O_frac;
}
void soot::GasState::setH2OFrac(double h2OFrac)
{
	H2O_frac = h2OFrac;
}
double soot::GasState::getCoFrac() const
{
	return CO_frac;
}
void soot::GasState::setCoFrac(double coFrac)
{
	CO_frac = coFrac;
}
double soot::GasState::getElementalCFrac() const
{
	return elementalC_frac;
}
void soot::GasState::setElementalCFrac(double elementalCFrac)
{
	elementalC_frac = elementalCFrac;
}
double soot::GasState::getElementalHFrac() const
{
	return elementalH_frac;
}
void soot::GasState::setElementalHFrac(double elementalHFrac)
{
	elementalH_frac = elementalHFrac;
}
soot::GasState::GasState()
{
	T = 0;
	P = 0;
	rho = 0;
	MW = 0;
	mu = 0;
	C2H2_frac = 0;
	O2_frac = 0;
	H_frac = 0;
	H2_frac = 0;
	OH_frac = 0;
	H2O_frac = 0;
	CO_frac = 0;
	elementalC_frac = 0;
	elementalH_frac = 0;
}
