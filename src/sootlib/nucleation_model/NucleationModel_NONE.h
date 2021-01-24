#ifndef NUCLEATIONMODEL_NONE_H
#define NUCLEATIONMODEL_NONE_H

#include "sootlib/nucleation_model/NucleationModel.h"

namespace soot
{
class NucleationModel_NONE : public NucleationModel
{
public:
	[[nodiscard]] double getNucleationRate() const override
	{
		return 0.0;
	}
};
}

#endif //NUCLEATIONMODEL_NONE_H
