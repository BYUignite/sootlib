#include "MomentSootState.h"
double soot::MomentSootState::getRho() const
{
	return rhoSoot;
}
void soot::MomentSootState::setRhoSoot(double rhoSoot)
{
	MomentSootState::rhoSoot = rhoSoot;
}
double soot::MomentSootState::getCmin() const
{
	return Cmin;
}
void soot::MomentSootState::setCmin(double cmin)
{
	Cmin = cmin;
}
double soot::MomentSootState::getDimer() const
{
	return dimer;
}
void soot::MomentSootState::setDimer(double dimer)
{
	MomentSootState::dimer = dimer;
}
double soot::MomentSootState::getMDimer() const
{
	return m_dimer;
}
void soot::MomentSootState::setMDimer(double mDimer)
{
	m_dimer = mDimer;
}
soot::MomentSootState::MomentSootState()
{
	rhoSoot = 0;
	Cmin = 0;
	dimer = 0;
	m_dimer = 0;
}
void soot::MomentSootState::setNumMoments(size_t n)
{
	moments = std::vector<double>(n, 0.0);
}
double soot::MomentSootState::getMoment(size_t i) const
{
	if (i > moments.size())
	{
		std::stringstream ss;
		ss << i << " out of bounds for MomentSootState with " << moments.size() << " soot vars";
		throw std::domain_error(ss.str());
	}
	return moments.at(i);
}
void soot::MomentSootState::setMoment(size_t i, double value)
{
	if (i > moments.size())
	{
		std::stringstream ss;
		ss << i << " out of bounds for MomentSootState with " << moments.size() << " soot vars";
		throw std::domain_error(ss.str());
	}
	moments.at(i) = value;
}
size_t soot::MomentSootState::getNumMoments() const
{
	return moments.size();
}
