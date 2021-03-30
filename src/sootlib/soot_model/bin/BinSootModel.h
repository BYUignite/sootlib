#ifndef BINSOOTMODEL_H
#define BINSOOTMODEL_H

#include "sootlib/SourceTerms.h"
#include "sootlib/state/BinState.h"

namespace soot
{
class BinSootModel
{
public:
	[[nodiscard]] virtual SourceTerms getSourceTerms(const BinState& state) const = 0;

	virtual ~BinSootModel() = default;
};
}

#endif //BINSOOTMODEL_H
