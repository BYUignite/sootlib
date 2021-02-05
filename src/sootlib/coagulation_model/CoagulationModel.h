#ifndef COAGULATIONMODEL_H
#define COAGULATIONMODEL_H

namespace soot
{
class CoagulationModel
{
public:
	[[nodiscard]] virtual double getCoagulationRate() const = 0;

	virtual ~CoagulationModel() = default;
};
}

#endif //COAGULATIONMODEL_H
