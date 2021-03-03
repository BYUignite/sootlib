#include "BaseState.h"
double soot::BaseState::getT() const
{
	return T;
}
void soot::BaseState::setT(double t)
{
	T = t;
}
double soot::BaseState::getP() const
{
	return P;
}
void soot::BaseState::setP(double p)
{
	P = p;
}
double soot::BaseState::getRhoGas() const
{
	return rhoGas;
}
void soot::BaseState::setRhoGas(double rhoGas)
{
	BaseState::rhoGas = rhoGas;
}
double soot::BaseState::getMwGas() const
{
	return MWGas;
}
void soot::BaseState::setMwGas(double mwGas)
{
	MWGas = mwGas;
}
double soot::BaseState::getMuGas() const
{
	return muGas;
}
void soot::BaseState::setMuGas(double muGas)
{
	BaseState::muGas = muGas;
}
double soot::BaseState::getGasSpeciesFrac(soot::GasSpecies species, double def) const
{
	if (gasFractions.count(species) == 0)
		return def;
	return gasFractions.at(species);
}
void soot::BaseState::setGasSpeciesFrac(soot::GasSpecies species, double frac)
{
	gasFractions[species] = frac;
}
double soot::BaseState::getGasSpeciesC(soot::GasSpecies species, double def) const
{
	if (gasFractions.count(species) == 0)
		return def;
	return rhoGas * gasFractions.at(species) / gasSpeciesMW.at(species);
}
double soot::BaseState::getGasSpeciesP(soot::GasSpecies species, double def) const
{
	if (gasFractions.count(species) == 0)
		return def;
	return gasFractions.at(species) * MWGas / gasSpeciesMW.at(species) * P;
}
double soot::BaseState::getPAHFrac(size_t n, double def) const
{
	if (PAHFractions.count(n) == 0)
		return def;
	return PAHFractions.at(n);
}
void soot::BaseState::setPAHFrac(size_t n, double frac)
{
	PAHFractions[n] = frac;
}
double soot::BaseState::getPAHC(size_t n, double def) const
{
	if (PAHFractions.count(n) == 0)
		return def;
	return rhoGas * PAHFractions.at(n) / PAH_MW(n);
}
double soot::BaseState::getPAHP(size_t n, double def) const
{
	if (PAHFractions.count(n) == 0)
		return def;
	return PAHFractions.at(n) * MWGas / PAH_MW(n) * P;
}
double soot::BaseState::getGasMeanFreePath() const
{
	return muGas / rhoGas * sqrt(M_PI * MWGas / (2.0 * Rg * T));
}
double soot::BaseState::getRhoSoot() const
{
	return rhoSoot;
}
void soot::BaseState::setRhoSoot(double rho)
{
	rhoSoot = rho;
}
double soot::BaseState::getCMin()
{
	if (!mDimerValid)
		calculateMDimer();
	return cMin;
}
double soot::BaseState::getDimer() const
{
	return dimer;
}
void soot::BaseState::setDimer(double dimer)
{
	BaseState::dimer = dimer;
}
void soot::BaseState::calculateMDimer()
{
	const double preFac = sqrt(4 * M_PI * kb * T) * pow(6.0 / (M_PI * rhoSoot), 2.0 / 3.0);

	wdotD = 0;
	mDimer = 0;
	// TODO this was not in the original code but it really looks like it's correct
	cMin = 0;

	double wDotI;
	double MPAHn;
	double N_n;
	const double exp = 1.0 / 6.0;
	for (const auto& [n, frac] : PAHFractions)
	{
		MPAHn = PAH_MW(n) / Na;
		N_n = getNi(n);
		wDotI = std::abs(getGammai(n) * preFac * pow(MPAHn, exp) * N_n * N_n);
		wdotD += wDotI;
		mDimer += wDotI * MPAHn;
		cMin += wDotI * MPAHn;
	}

	mDimer += 2 / wdotD;
	cMin *= 4 / wdotD;

	mDimerValid = true;
}
double soot::BaseState::getNi(size_t i) const
{
	return rhoGas * PAHFractions.at(i) / PAH_MW(i) * Na;
}
double soot::BaseState::getGammai(size_t i) const
{
	const double m_PAH = PAH_MW(i) / Na;
	return m_PAH > 153 ? 1.501E-11 * pow(m_PAH, 4) : 1.501E-11 * pow(m_PAH, 4) / 3.0;
}
double soot::BaseState::getMDimer()
{
	if (!mDimerValid)
		calculateMDimer();
	return mDimer;
}
double soot::BaseState::getWDotD()
{
	if (!mDimerValid)
		calculateMDimer();
	return wdotD;
}
std::map<soot::GasSpecies, double>::const_iterator soot::BaseState::gasFractionsBegin() const
{
	return gasFractions.begin();
}
std::map<soot::GasSpecies, double>::const_iterator soot::BaseState::gasFractionsEnd() const
{
	return gasFractions.end();
}
std::map<size_t, double>::const_iterator soot::BaseState::PAHFractionsBegin() const
{
	return PAHFractions.begin();
}
std::map<size_t, double>::const_iterator soot::BaseState::PAHFractionsEnd() const
{
	return PAHFractions.end();
}
