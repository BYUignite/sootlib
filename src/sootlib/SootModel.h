#ifndef SOOTMODEL_H
#define SOOTMODEL_H

#include <vector>

#include "sootlib/state/GasState.h"

namespace soot
{
class SootModel
{
public:
	[[nodiscard]] virtual std::vector<double> getSrc(const GasState& gasState) = 0;
};
}

#endif //SOOTMODEL_H
