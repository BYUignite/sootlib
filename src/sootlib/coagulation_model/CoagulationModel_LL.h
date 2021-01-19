#ifndef COAGULATIONMODEL_LL_H
#define COAGULATIONMODEL_LL_H

#include <cmath>

#include "CoagulationModel.h"

namespace soot
{
class CoagulationModel_LL : public CoagulationModel
{
public:
	CoagulationModel_LL(double m1, double m2);

	[[nodiscard]] double getCoagulationRate() const override;

private:
	double m1;
	double m2;
};
}

#endif //COAGULATIONMODEL_LL_H
