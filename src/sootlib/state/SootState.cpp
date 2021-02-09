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
