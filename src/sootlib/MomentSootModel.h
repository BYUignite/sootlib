#ifndef MOMENTSOOTMODEL_H
#define MOMENTSOOTMODEL_H

#include "sootlib/SootSourceTerms.h"
#include "sootlib/state/gas/GasState.h"
#include "sootlib/state/soot/MomentSootState.h"
#include "sootlib/soot_models/SootModel_Base.h"

namespace soot
{
class MomentSootModel : public SootModel_Base
{
public:
	[[nodiscard]] virtual SootSourceTerms getSourceTerms(const GasState& gasState, const MomentSootState& sootState) = 0;

	virtual ~MomentSootModel() = default;
};
}

#endif //MOMENTSOOTMODEL_H
