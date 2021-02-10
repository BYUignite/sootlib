#include "BinSootState.h"
size_t soot::BinSootState::getNumBins() const
{
	return bins.size();
}
void soot::BinSootState::setNumBins(size_t n)
{
	bins = std::vector<double>(n, 0.0);
}
double soot::BinSootState::getBin(size_t i) const
{
	return bins.at(i);
}
void soot::BinSootState::setBin(size_t i, double value)
{
	bins.at(i) = value;
}
