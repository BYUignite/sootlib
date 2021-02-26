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
double soot::GasState::getOHFrac() const
{
	return OH_frac;
}
void soot::GasState::setOHFrac(double ohFrac)
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
double soot::GasState::getCOFrac() const
{
	return CO_frac;
}
void soot::GasState::setCOFrac(double coFrac)
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
double soot::GasState::getC_C2H2() const
{
	return rho * C2H2_frac / MW_C2H2;
}
double soot::GasState::getC_O2() const
{
	return rho * O2_frac / MW_O2;
}
double soot::GasState::getC_H() const
{
	return rho * H_frac / MW_H;
}
double soot::GasState::getC_H2() const
{
	return rho * H2_frac / MW_H2;
}
double soot::GasState::getC_OH() const
{
	return rho * OH_frac / MW_OH;
}
double soot::GasState::getC_H2O() const
{
	return rho * H2O_frac / MW_H2O;
}
double soot::GasState::getC_CO() const
{
	return rho * CO_frac / MW_CO;
}
double soot::GasState::getC_elementalC() const
{
	return rho * elementalC_frac / MW_C;
}
double soot::GasState::getC_elementalH() const
{
	return rho * elementalH_frac / MW_H;
}
double soot::GasState::getP_C2H2() const
{
	return C2H2_frac * MW / MW_C2H2 * P;
}
double soot::GasState::getP_O2() const
{
	return O2_frac * MW / MW_O2 * P;
}
double soot::GasState::getP_H() const
{
	return H_frac * MW / MW_H * P;
}
double soot::GasState::getP_H2() const
{
	return H2_frac * MW / MW_H2 * P;
}
double soot::GasState::getP_OH() const
{
	return OH_frac * MW / MW_OH * P;
}
double soot::GasState::getP_H2O() const
{
	return H2O_frac * MW / MW_H2O * P;
}
double soot::GasState::getP_CO() const
{
	return CO_frac * MW / MW_CO * P;
}
double soot::GasState::getP_elementalC() const
{
	return elementalC_frac * MW / MW_C * P;
}
double soot::GasState::getP_elementalH() const
{
	return elementalH_frac * MW / MW_H * P;
}
double soot::GasState::getGasMeanFreePath() const
{
	return mu / rho * sqrt(M_PI * MW / (2.0 * Rg * T));
}
soot::GasComponent soot::GasState::getPAH(size_t n, GasComponent def) const
{
	if (PAHs.count(n) == 0)
		return def;
	return PAHs.at(n);
}
double soot::GasState::getPAHFrac(size_t n, double def) const
{
	if (PAHs.count(n) == 0)
		return def;
	return PAHs.at(n).y;
}
double soot::GasState::getPAHMW(size_t n, double def) const
{
	if (PAHs.count(n) == 0)
		return def;
	return PAHs.at(n).MW;
}
double soot::GasState::getC_PAH(size_t n, double def) const
{
	if (PAHs.count(n) == 0)
		return def;
	return rho * PAHs.at(n).y / PAHs.at(n).MW;
}
double soot::GasState::getP_PAH(size_t n, double def) const
{
	if (PAHs.count(n) == 0)
		return def;
	return PAHs.at(n).y * MW / PAHs.at(n).MW * P;
}
void soot::GasState::setPAH(size_t n, soot::GasComponent comp)
{
	PAHs[n] = comp;
}
void soot::GasState::setPAH(size_t n, double frac, double MW)
{
	PAHs[n] = {frac, MW};
}
size_t soot::GasState::getNumPAH() const
{
	return PAHs.size();
}
