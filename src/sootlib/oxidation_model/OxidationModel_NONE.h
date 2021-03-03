#ifndef OXIDATIONMODEL_NONE_H
#define OXIDATIONMODEL_NONE_H

#include "sootlib/oxidation_model/OxidationModel.h"

namespace soot
{
class OxidationModel_NONE : public OxidationModel
{
public:
	[[nodiscard]] double getOxidationRate(const MomentState& state) const override
	{
		return 0;
	}

	~OxidationModel_NONE() override = default;
};
}

#endif //OXIDATIONMODEL_NONE_H
