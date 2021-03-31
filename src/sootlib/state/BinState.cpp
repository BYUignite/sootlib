#include "BinState.h"

using namespace soot;

BinState::BinState(size_t numBins)
{
	if (numBins != 0)
		resetBins(numBins);
}
size_t BinState::getNumBins() const
{
	return bins.size();
}
void BinState::resetBins(size_t numBins)
{
	bins = std::vector<double>(numBins, 0);
}
double BinState::getBin(size_t i) const
{
	return bins.at(i);
}
void BinState::setBin(size_t i, double value)
{
	bins.at(i) = value;
}
