#include "psdModel.h"

using namespace std;
using namespace soot;

psdModel::psdModel(sourceTermStruct& sourceTerms, int nVar, nucleationMech N, growthMech G, oxidationMech X, coagulationMech C) {

    //---------- set nucleation model

    switch (N) {
        case nucleationMech::NONE: nuc = new nucleationModel_NONE();
        case nucleationMech::LL:   nuc = new nucleationModel_LL();
        case nucleationMech::LIN:  nuc = new nucleationModel_LIN();
        case nucleationMech::PAH:  nuc = new nucleationModel_PAH();
        default: throw domain_error("Invalid soot nucleation mechanism requested");
    }

    //---------- set growth model

    switch (G) {
        case growthMech::NONE: grw = new growthModel_NONE();
        case growthMech::LL:   grw = new growthModel_LL();
        case growthMech::LIN:  grw = new growthModel_LIN();
        case growthMech::HACA: grw = new growthModel_HACA();
        default: throw domain_error("Invalid soot growth mechanism requested");
    }

    //---------- set oxidation model

    switch (X) {
        case oxidationMech::NONE:     oxi = new oxidationModel_NONE();
        case oxidationMech::LL:       oxi = new oxidationModel_LL();
        case oxidationMech::LEE_NEOH: oxi = new oxidationModel_LEE_NEOH();
        case oxidationMech::NSC_NEOH: oxi = new oxidationModel_NSC_NEOH();
        case oxidationMech::HACA:     oxi = new oxidationModel_HACA();
        default: throw domain_error("Invalid soot oxidation model requested");
    }

    //---------- set coagulation model

    switch (C) {
        case coagulationMech::NONE:  coa = new coagulationModel_NONE();
        case coagulationMech::LL:    coa = new coagulationModel_LL();
        case coagulationMech::FUCHS: coa = new coagulationModel_FUCHS();
        case coagulationMech::FRENK: coa = new coagulationModel_FRENK();
        default: throw domain_error("Invalid soot coagulation mechanism requested");
    }


}
