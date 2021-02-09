#ifndef SOOTMODEL_H
#define SOOTMODEL_H

#include <vector>

#include <sootlib/state/GasState.h>
#include <sootlib/state/SootState.h>

namespace soot
{
class SootModel
{
public:
	[[nodiscard]] virtual std::vector<double> getSourceTerms(const GasState& gasState, const SootState& sootState) = 0;

	virtual ~SootModel() = default;
};
}

#endif //SOOTMODEL_H
