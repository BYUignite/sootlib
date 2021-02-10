#ifndef BINSOOTMODEL_H
#define BINSOOTMODEL_H

#include "sootlib/SootSourceTerms.h"
#include "sootlib/state/GasState.h"
#include "sootlib/state/BinSootState.h"
#include "sootlib/soot_models/SootModel_Base.h"

namespace soot
{
class BinSootModel : public SootModel_Base
{
public:
	[[nodiscard]] virtual SootSourceTerms getSourceTerms(const GasState& gasState, const BinSootState& sootState) = 0;

	virtual ~BinSootModel() = default;
};
}

#endif //BINSOOTMODEL_H
