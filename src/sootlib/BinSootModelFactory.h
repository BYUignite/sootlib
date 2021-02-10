#ifndef BINSOOTMODELFACTORY_H
#define BINSOOTMODELFACTORY_H

#include <memory>

#include "sootlib/SootModelFactory.h"
#include "sootlib/BinSootModel.h"
#include "sootlib/soot_models/bin/SootModel_SECT.h"

namespace soot
{
class BinSootModelFactory : public SootModelFactory
{
public:
	BinSootModelFactory();

	void setModel(BinModel model);

	[[nodiscard]] BinSootModel* getModel() const;
	[[nodiscard]] std::unique_ptr<BinSootModel> getModelUnique() const;
	[[nodiscard]] std::shared_ptr<BinSootModel> getModelShared() const;

private:
	BinModel model;
};
}

#endif //BINSOOTMODELFACTORY_H
