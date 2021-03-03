#include "MomentState.h"
soot::MomentState::MomentState(size_t numMoments)
{
	if (numMoments != 0)
		resetMoments(numMoments);
}
size_t soot::MomentState::getNumMoments() const
{
	return moments.size();
}
void soot::MomentState::resetMoments(size_t numMoments)
{
	moments = std::vector<double>(numMoments, 0);
}
double soot::MomentState::getMoment(size_t i) const
{
	return moments.at(i);
}
void soot::MomentState::setMoment(size_t i, double value)
{
	moments.at(i) = value;
}
