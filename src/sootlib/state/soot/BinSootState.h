#ifndef BINSOOTSTATE_H
#define BINSOOTSTATE_H

#include <sstream>
#include <vector>

#include "sootlib/state/soot/BaseSootState.h"

namespace soot
{
class BinSootState : public BaseSootState
{
public:
	/* Getters and setters */

	[[nodiscard]] size_t getNumBins() const;
	void setNumBins(size_t n);
	[[nodiscard]] double getBin(size_t i) const;
	void setBin(size_t i, double value);

private:
	/* Soot properties */

	// soot bins
	// Units: #
	std::vector<double> bins;
};
}

#endif //BINSOOTSTATE_H
