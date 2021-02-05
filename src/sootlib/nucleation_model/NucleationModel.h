#ifndef NUCLEATIONMODEL_H
#define NUCLEATIONMODEL_H

namespace soot
{
class NucleationModel
{
public:
	[[nodiscard]] virtual double getNucleationRate() const = 0;

	virtual ~NucleationModel() = default;
};
}

#endif //NUCLEATIONMODEL_H
