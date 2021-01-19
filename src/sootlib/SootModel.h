#ifndef SOOTMODEL_H
#define SOOTMODEL_H

#include <vector>

#include "sootlib/gas/GasState.h"

namespace soot
{
class SootModel
{
public:
	// TODO don't know how necessary this is
	virtual GasState& gasState() = 0;

	[[nodiscard]] virtual size_t getNumSootVars() const = 0;
	[[nodiscard]] virtual double getSootQuantity(size_t index) const = 0;
	[[nodiscard]] virtual double getGasSootSource(size_t index) const = 0;
	[[nodiscard]] virtual double getSourceTerm(size_t index) const = 0;
};
}

#endif //SOOTMODEL_H
