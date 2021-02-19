#ifndef BINSOOTMODELGENERATOR_H
#define BINSOOTMODELGENERATOR_H

#include <memory>

#include "SootModelGenerator.h"
#include "sootlib/soot_models/bin/BinSootModel.h"
#include "sootlib/soot_models/bin/SootModel_SECT.h"

namespace soot
{
class BinSootModelGenerator : public SootModelGenerator
{
public:
	BinSootModelGenerator();

	void setModel(BinModel model);

	[[nodiscard]] BinSootModel* getModel() const;
	[[nodiscard]] std::unique_ptr<BinSootModel> getModelUnique() const;
	[[nodiscard]] std::shared_ptr<BinSootModel> getModelShared() const;

private:
	BinModel model;
};
}

#endif //BINSOOTMODELGENERATOR_H
