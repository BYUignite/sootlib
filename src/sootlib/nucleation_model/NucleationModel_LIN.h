#ifndef NUCLEATIONMODEL_LIN_H
#define NUCLEATIONMODEL_LIN_H

#include "sootlib/nucleation_model/NucleationModel.h"

namespace soot
{
class NucleationModel_LIN : public NucleationModel
{
public:
	// TODO implement
	[[nodiscard]] double getNucleationRate() const override;

	~NucleationModel_LIN() override = default;
};
}

#endif //NUCLEATIONMODEL_LIN_H
