#ifndef MOMENTSOOTMODELGENERATOR_H
#define MOMENTSOOTMODELGENERATOR_H

#include "SootModelGenerator.h"

/* soot models */
#include "sootlib/soot_model/moment/SootModel_LOGN.h"
#include "sootlib/soot_model/moment/SootModel_MOMIC.h"
#include "sootlib/soot_model/moment/SootModel_MONO.h"
#include "sootlib/soot_model/moment/SootModel_QMOM.h"

namespace soot {
class MomentSootModelGenerator : public SootModelGenerator {
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
