#ifndef OXIDATIONMODEL_LL_H
#define OXIDATIONMODEL_LL_H

#include "sootlib/oxidation_model/OxidationModel.h"

namespace soot
{
class OxidationModel_LL : public OxidationModel
{
public:
	[[nodiscard]] double getOxidationRate() const override
	{
		return 0.0;
	}
};
}

#endif //OXIDATIONMODEL_LL_H
