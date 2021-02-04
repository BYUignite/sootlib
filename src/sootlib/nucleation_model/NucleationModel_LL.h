#ifndef NUCLEATIONMODEL_LL_H
#define NUCLEATIONMODEL_LL_H

#include "sootlib/nucleation_model/NucleationModel.h"

namespace soot
{
class NucleationModel_LL : public NucleationModel
{
public:
	// TODO implement
	[[nodiscard]] double getNucleationRate() const override;

	~NucleationModel_LL() override = default;
};
}

#endif //NUCLEATIONMODEL_LL_H
