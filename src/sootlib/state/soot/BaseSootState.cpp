#include "BaseSootState.h"
soot::BaseSootState::BaseSootState()
{
	rho = 0;
	cMin = 0;
	dimer = 0;
	mDimer = 0;
}
double soot::BaseSootState::getRho() const
{
	return rho;
}
void soot::BaseSootState::setRho(double rho)
{
	this->rho = rho;
}
double soot::BaseSootState::getCMin() const
{
	return cMin;
}
void soot::BaseSootState::setCMin(double cMin)
{
	this->cMin = cMin;
}
double soot::BaseSootState::getDimer() const
{
	return dimer;
}
void soot::BaseSootState::setDimer(double dimer)
{
	this->dimer = dimer;
}
double soot::BaseSootState::getMDimer() const
{
	return mDimer;
}
void soot::BaseSootState::setMDimer(double mDimer)
{
	this->mDimer = mDimer;
}
