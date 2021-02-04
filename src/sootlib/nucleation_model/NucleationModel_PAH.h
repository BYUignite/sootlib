#ifndef NUCLEATIONMODEL_PAH_H
#define NUCLEATIONMODEL_PAH_H

#include "sootlib/nucleation_model/NucleationModel.h"

namespace soot
{
class NucleationModel_PAH : public NucleationModel
{
public:
	// TODO implement
	[[nodiscard]] double getNucleationRate() const override;

	~NucleationModel_PAH() override = default;
};
}

#endif //NUCLEATIONMODEL_PAH_H
