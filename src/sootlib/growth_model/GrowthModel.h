#ifndef GROWTHMODEL_H
#define GROWTHMODEL_H

namespace soot
{
class GrowthModel
{
public:
	[[nodiscard]] virtual double getGrowthRate() const = 0;

	virtual ~GrowthModel() = 0;
};
}

#endif //GROWTHMODEL_H
