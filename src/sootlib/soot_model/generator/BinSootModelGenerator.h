#ifndef BINSOOTMODELGENERATOR_H
#define BINSOOTMODELGENERATOR_H

#include "SootModelGenerator.h"

/* soot models */
#include "sootlib/soot_model/bin/SootModel_SECT.h"

namespace soot {
class BinSootModelGenerator : public SootModelGenerator {
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
