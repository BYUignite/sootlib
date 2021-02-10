#include "MomentSootState.h"
double soot::MomentSootState::getMoment(size_t i) const
{
	if (i > moments.size())
	{
		std::stringstream ss;
		ss << i << " out of bounds for MomentSootState with " << moments.size() << " moments";
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
void soot::MomentSootState::setNumMoments(size_t n)
{
	moments = std::vector<double>(n, 0.0);
}
