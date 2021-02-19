#ifndef MOMENTSOOTMODELGENERATOR_H
#define MOMENTSOOTMODELGENERATOR_H

#include <memory>

#include "SootModelGenerator.h"
#include "sootlib/soot_models/moment/MomentSootModel.h"

namespace soot
{
class MomentSootModelGenerator : public SootModelGenerator
{
public:
	MomentSootModelGenerator();

	void setModel(MomentModel model);

	[[nodiscard]] MomentSootModel* getModel() const;
	[[nodiscard]] std::unique_ptr<MomentSootModel> getModelUnique() const;
	[[nodiscard]] std::shared_ptr<MomentSootModel> getModelShared() const;

private:
	MomentModel model;
};
}

#endif //MOMENTSOOTMODELGENERATOR_H
