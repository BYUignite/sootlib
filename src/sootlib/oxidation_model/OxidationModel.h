#ifndef OXIDATIONMODEL_H
#define OXIDATIONMODEL_H

namespace soot
{
class OxidationModel
{
public:
	[[nodiscard]] virtual double getOxidationRate() const = 0;

	virtual ~OxidationModel() = default;
};
}

#endif //OXIDATIONMODEL_H
