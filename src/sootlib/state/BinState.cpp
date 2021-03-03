#include "BinState.h"
soot::BinState::BinState(size_t numBins)
{
	if (numBins != 0)
		resetBins(numBins);
}
size_t soot::BinState::getNumBins() const
{
	return bins.size();
}
void soot::BinState::resetBins(size_t numBins)
{
	bins = std::vector<double>(numBins, 0);
}
double soot::BinState::getBin(size_t i) const
{
	return bins.at(i);
}
void soot::BinState::setBin(size_t i, double value)
{
	bins.at(i) = value;
}
