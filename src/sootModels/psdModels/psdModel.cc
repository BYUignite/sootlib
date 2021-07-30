#include "psdModel.h"

using namespace std;
using namespace soot;

psdModel::psdModel(sourceTermStruct& sourceTerms, int nVar, nucleationMech N, growthMech G, oxidationMech X, coagulationMech C) {

    //---------- set nucleation model

    if      (N == nucleationMech::NONE) { nuc = new nucleationModel_NONE(); }
    else if (N == nucleationMech::LL)   { nuc = new nucleationModel_LL();   }
    else if (N == nucleationMech::LIN)  { nuc = new nucleationModel_LIN();  }
    else if (N == nucleationMech::PAH)  { nuc = new nucleationModel_PAH();  }
    else throw domain_error("Invalid nucleation model requested");

    //---------- set growth model

    if      (G == growthMech::NONE) { grw = new growthModel_NONE(); }
    else if (G == growthMech::LL)   { grw = new growthModel_LL();   }
    else if (G == growthMech::LIN)  { grw = new growthModel_LIN();  }
    else if (G == growthMech::HACA) { grw = new growthModel_HACA(); }
    else throw domain_error("Invalid growth model requested");

    //---------- set oxidation model

    if      (X == oxidationMech::NONE)     { oxi = new oxidationModel_NONE();    }
    else if (X == oxidationMech::LL)       { oxi = new oxidationModel_LL();      }
    else if (X == oxidationMech::LEE_NEOH) { oxi = new oxidationModel_LEE_NEOH();}
    else if (X == oxidationMech::NSC_NEOH) { oxi = new oxidationModel_NSC_NEOH();}
    else if (X == oxidationMech::HACA)     { oxi = new oxidationModel_HACA();    }
    else throw domain_error("Invalid oxidation model requested");

    //---------- set coagulation model

    if      (C == coagulationMech::NONE)  { coa = new coagulationModel_NONE(); }
    else if (C == coagulationMech::LL)    { coa = new coagulationModel_LL();   }
    else if (C == coagulationMech::FUCHS) { coa = new coagulationModel_FUCHS();}
    else if (C == coagulationMech::FRENK) { coa = new coagulationModel_FRENK();}
    else throw domain_error("Invalid coagulation model requested");

}
