#include "State.h"
double soot::State::getT() const
{
	return T;
}
void soot::State::setT(double t)
{
	T = t;
	goodMDimerValue = false;
}
double soot::State::getP() const
{
	return P;
}
void soot::State::setP(double p)
{
	P = p;
}
double soot::State::getGasRho() const
{
	return gasRho;
}
void soot::State::setGasRho(double rho)
{
	gasRho = rho;
	goodMDimerValue = false;
}
double soot::State::getMw() const
{
	return MW;
}
void soot::State::setMw(double mw)
{
	MW = mw;
}
double soot::State::getMu() const
{
	return mu;
}
void soot::State::setMu(double mu)
{
	State::mu = mu;
}
soot::GasComponent& soot::State::PAH(size_t numC)
{
	goodMDimerValue = false;
	return PAHdata[numC];
}
double soot::State::getC2H2Frac() const
{
	return C2H2_frac;
}
void soot::State::setC2H2Frac(double c2H2Frac)
{
	C2H2_frac = c2H2Frac;
}
double soot::State::getO2Frac() const
{
	return O2_frac;
}
void soot::State::setO2Frac(double o2Frac)
{
	O2_frac = o2Frac;
}
double soot::State::getHFrac() const
{
	return H_frac;
}
void soot::State::setHFrac(double hFrac)
{
	H_frac = hFrac;
}
double soot::State::getH2Frac() const
{
	return H2_frac;
}
void soot::State::setH2Frac(double h2Frac)
{
	H2_frac = h2Frac;
}
double soot::State::getOHFrac() const
{
	return OH_frac;
}
void soot::State::setOHFrac(double ohFrac)
{
	OH_frac = ohFrac;
}
double soot::State::getH2OFrac() const
{
	return H2O_frac;
}
void soot::State::setH2OFrac(double h2OFrac)
{
	H2O_frac = h2OFrac;
}
double soot::State::getCOFrac() const
{
	return CO_frac;
}
void soot::State::setCOFrac(double coFrac)
{
	CO_frac = coFrac;
}
double soot::State::getElementalCFrac() const
{
	return elementalC_frac;
}
void soot::State::setElementalCFrac(double elementalCFrac)
{
	elementalC_frac = elementalCFrac;
}
double soot::State::getElementalHFrac() const
{
	return elementalH_frac;
}
void soot::State::setElementalHFrac(double elementalHFrac)
{
	elementalH_frac = elementalHFrac;
}
double soot::State::getC_C2H2() const
{
	return gasRho * C2H2_frac / MW_C2H2;
}
double soot::State::getC_O2() const
{
	return gasRho * O2_frac / MW_O2;
}
double soot::State::getC_H() const
{
	return gasRho * H_frac / MW_H;
}
double soot::State::getC_H2() const
{
	return gasRho * H2_frac / MW_H2;
}
double soot::State::getC_OH() const
{
	return gasRho * OH_frac / MW_OH;
}
double soot::State::getC_H2O() const
{
	return gasRho * H2O_frac / MW_H2O;
}
double soot::State::getC_CO() const
{
	return gasRho * CO_frac / MW_CO;
}
double soot::State::getC_elementalC() const
{
	return gasRho * elementalC_frac / MW_C;
}
double soot::State::getC_elementalH() const
{
	return gasRho * elementalH_frac / MW_H;
}
double soot::State::getP_C2H2() const
{
	return C2H2_frac * MW / MW_C2H2 * P;
}
double soot::State::getP_O2() const
{
	return O2_frac * MW / MW_O2 * P;
}
double soot::State::getP_H() const
{
	return H_frac * MW / MW_H * P;
}
double soot::State::getP_H2() const
{
	return H2_frac * MW / MW_H2 * P;
}
double soot::State::getP_OH() const
{
	return OH_frac * MW / MW_OH * P;
}
double soot::State::getP_H2O() const
{
	return H2O_frac * MW / MW_H2O * P;
}
double soot::State::getP_CO() const
{
	return CO_frac * MW / MW_CO * P;
}
double soot::State::getP_elementalC() const
{
	return elementalC_frac * MW / MW_C * P;
}
double soot::State::getP_elementalH() const
{
	return elementalH_frac * MW / MW_H * P;
}
double soot::State::getGasMeanFreePath() const
{
	return mu / gasRho * sqrt(M_PI * MW / (2.0 * Rg * T));
}
soot::GasComponent soot::State::getPAH(size_t n, GasComponent def) const
{
	if (PAHdata.count(n) == 0)
		return def;
	return PAHdata.at(n);
}
double soot::State::getPAHFrac(size_t n, double def) const
{
	if (PAHspecies.count(n) == 0)
		return def;
	return PAHdata.at(n).y;
}
double soot::State::getPAHMW(size_t n, double def) const
{
	if (PAHspecies.count(n) == 0)
		return def;
	return PAHdata.at(n).MW;
}
double soot::State::getC_PAH(size_t n, double def) const
{
	if (PAHspecies.count(n) == 0)
		return def;
	return gasRho * PAHdata.at(n).y / PAHdata.at(n).MW;
}
double soot::State::getP_PAH(size_t n, double def) const
{
	if (PAHspecies.count(n) == 0)
		return def;
	return PAHdata.at(n).y * MW / PAHdata.at(n).MW * P;
}
void soot::State::setPAH(size_t n, soot::GasComponent comp)
{
	PAHdata[n] = comp;
	PAHspecies.insert(n);
	goodMDimerValue = false;
}
void soot::State::setPAH(size_t n, double frac, double MW)
{
	PAHdata[n] = {frac, MW};
	PAHspecies.insert(n);
	goodMDimerValue = false;
}
size_t soot::State::getNumPAH() const
{
	return PAHdata.size();
}
const std::set<size_t>& soot::State::getPAHSpecies() const
{
	return PAHspecies;
}
double soot::State::getM_PAH(size_t n, double def) const
{
	if (PAHspecies.count(n) == 0)
		return def;

	return PAHdata.at(n).MW / Na;
}
double soot::State::getGammai(size_t n, double def) const
{
	if (PAHspecies.count(n) == 0)
		return def;

	const double m_PAH = getM_PAH(n);
	return m_PAH > 153 ? 1.501E-11 * pow(m_PAH, 4) : 1.501E-11 * pow(m_PAH, 4) / 3.0;
}
double soot::State::getNi(size_t n, double def) const
{
	if (PAHspecies.count(n) == 0)
		return def;

	return gasRho * PAHdata.at(n).y / PAHdata.at(n).MW * Na;
}
void soot::State::calculateDimer()
{
	const double preFac = sqrt(4 * M_PI * kb * T) * pow(6.0 / (M_PI * sootRho), 2.0 / 3.0);

	wdotD = 0;
	mDimer = 0;

	double wDotI;
	for (const auto& [n, comp] : PAHdata)
	{
		const double MPAHn = getM_PAH(n);
		const double N_n = getNi(n);
		wDotI = std::abs(getGammai(n) * preFac * pow(MPAHn, 1.0 / 6.0) * N_n * N_n);
		wdotD += wDotI;
		mDimer += wDotI * MPAHn;
		cMin += wDotI * MPAHn;
		// There's some code missing here dealing with the ratio stuff
	}

	mDimer *= 2 / wdotD;
	cMin *= 4 / wdotD;

	goodMDimerValue = true;
}
double soot::State::getSootRho() const
{
	return sootRho;
}
void soot::State::setSootRho(double rho)
{
	sootRho = rho;
}
double soot::State::getCMin() const
{
	return cMin;
}
double soot::State::getDimer() const
{
	return dimer;
}
double soot::State::getMDimer()
{
	if (!goodMDimerValue)
		calculateDimer();
	return mDimer;
}
double soot::State::getWDotD()
{
	if (!goodMDimerValue)
		calculateDimer();
	return wdotD;
}
