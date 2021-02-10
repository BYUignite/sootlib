#ifndef MOMENTSOOTMODELFACTORY_H
#define MOMENTSOOTMODELFACTORY_H

#include <memory>

#include "sootlib/SootModelFactory.h"
#include "sootlib/MomentSootModel.h"

namespace soot
{
class MomentSootModelFactory : public SootModelFactory
{
public:
	MomentSootModelFactory();

	void setModel(MomentModel model);

	[[nodiscard]] MomentSootModel* getModel() const;
	[[nodiscard]] std::unique_ptr<MomentSootModel> getModelUnique() const;
	[[nodiscard]] std::shared_ptr<MomentSootModel> getModelShared() const;

private:
	MomentModel model;
};
}

#endif //MOMENTSOOTMODELFACTORY_H
