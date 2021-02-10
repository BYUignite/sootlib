#ifndef MOMENTSOOTSTATE_H
#define MOMENTSOOTSTATE_H

#include <sstream>
#include <vector>

#include "sootlib/state/soot/BaseSootState.h"

namespace soot
{
class MomentSootState : public BaseSootState
{
public:
	/* Getters and setters */

	[[nodiscard]] size_t getNumMoments() const;
	void setNumMoments(size_t n);
	[[nodiscard]] double getMoment(size_t i) const;
	void setMoment(size_t i, double value);

private:
	/* Soot properties */

	// soot moments
	// Units: #/m3, kg/m3, kg2/m3, ...
	std::vector<double> moments;
};
}

#endif //MOMENTSOOTSTATE_H
