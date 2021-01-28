#ifndef SOOTMODEL_H
#define SOOTMODEL_H

#include <vector>

#include "sootlib/state/GasState.h"

namespace soot
{
class SootModel
{
public:
	// TODO document this function
	// does this need a soot state?
	[[nodiscard]] virtual std::vector<double> getSourceTerms(const GasState& gasState) = 0;

	virtual ~SootModel() = 0;
};
}

#endif //SOOTMODEL_H
