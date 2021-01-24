#ifndef SOOTMODEL_MONO_H
#define SOOTMODEL_MONO_H

#include <vector>

#include "sootlib/state/GasState.h"
#include "sootlib/SootModel_Base.h"

namespace soot
{
class SootModel_MONO : public SootModel_Base
{
public:
	[[nodiscard]] static SootModel_MONO getInstance(/*params*/);

	[[nodiscard]] std::vector<double> getSrc(const GasState& gasState) override;

private:
	SootModel_MONO() = default;
};
}

#endif //SOOTMODEL_MONO_H
