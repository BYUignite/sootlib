#ifndef NUCLEATIONMODEL_H
#define NUCLEATIONMODEL_H

namespace soot
{
class NucleationModel
{
	[[nodiscard]] virtual double getNucleationRate() const = 0;
};
}

#endif //NUCLEATIONMODEL_H
