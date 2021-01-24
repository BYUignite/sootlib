#ifndef OXIDATIONMODEL_H
#define OXIDATIONMODEL_H

namespace soot
{
class OxidationModel
{
public:
	[[nodiscard]] virtual double getOxidationRate() const = 0;
};
}

#endif //OXIDATIONMODEL_H
