#ifndef MOMENTSOOTMODEL_H
#define MOMENTSOOTMODEL_H

#include <vector>

#include <sootlib/state/GasState.h>
#include <sootlib/state/MomentSootState.h>

namespace soot
{
class MomentSootModel
{
public:
	[[nodiscard]] virtual std::vector<double> getSourceTerms(const GasState& gasState, const MomentSootState& sootState) = 0;

	virtual ~MomentSootModel() = default;
};
}

#endif //MOMENTSOOTMODEL_H
