#include "SootState.h"
double soot::SootState::getRho() const
{
	return rhoSoot;
}
void soot::SootState::setRhoSoot(double rhoSoot)
{
	SootState::rhoSoot = rhoSoot;
}
double soot::SootState::getCmin() const
{
	return Cmin;
}
void soot::SootState::setCmin(double cmin)
{
	Cmin = cmin;
}
double soot::SootState::getDimer() const
{
	return dimer;
}
void soot::SootState::setDimer(double dimer)
{
	SootState::dimer = dimer;
}
double soot::SootState::getMDimer() const
{
	return m_dimer;
}
void soot::SootState::setMDimer(double mDimer)
{
	m_dimer = mDimer;
}
soot::SootState::SootState()
{
	rhoSoot = 0;
	Cmin = 0;
	dimer = 0;
	m_dimer = 0;
}
void soot::SootState::setNumSootVars(size_t n)
{
	sootVars = std::vector<double>(n, 0.0);
}
double soot::SootState::getSootVar(size_t i) const
{
	if (i > sootVars.size())
	{
		std::stringstream ss;
		ss << i << " out of bounds for SootState with " << sootVars.size() << " soot vars";
		throw std::domain_error(ss.str());
	}
	return sootVars.at(i);
}
void soot::SootState::setSootVar(size_t i, double value)
{
	if (i > sootVars.size())
	{
		std::stringstream ss;
		ss << i << " out of bounds for SootState with " << sootVars.size() << " soot vars";
		throw std::domain_error(ss.str());
	}
	sootVars.at(i) = value;
}
