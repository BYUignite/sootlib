#ifndef SOOTMODEL_BASE_H
#define SOOTMODEL_BASE_H

#include "sootlib/gas/GasState.h"
#include "SootModel.h"
#include "static.h"

namespace soot
{
class SootModel_Base : public SootModel
{
public:
	GasState& gasState() override;

	// TODO one of these probably shouldn't be implemented so that this is a virutal class
	// this is going to depend on the structure of the original functionality
	[[nodiscard]] size_t getNumSootVars() const override;
	[[nodiscard]] double getSootQuantity(size_t index) const override;
	[[nodiscard]] double getGasSootSource(size_t index) const override;
	[[nodiscard]] double getSourceTerm(size_t index) const override;

	// TODO at least some of this should probably be protected since this is going to be a virtual class
private:
	NucleationMechanism nucleationMechanism;
	GrowthMechanism growthMechanism;
	OxidationMechanism oxidationMechanism;
	CoagulationMechanism coagulationMechanism;

	double Cmin;
	double dimer;
	double m_dimer;

	// stuff

	GasState gasState_;
};
}

#endif //SOOTMODEL_BASE_H
