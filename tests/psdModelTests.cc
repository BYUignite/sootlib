#include <catch2/catch.hpp>

#include "sootModel.h"
#include "constants.h"

using namespace std;
using namespace soot;

////////////////////////////////////////////////////////////////////////////////

TEST_CASE("psdModel object initialization", "[psdModel]") {

    SECTION("PSD models with NONE soot chemistry") {

        nucleationMech  n = nucleationMech::NONE;
        growthMech      g = growthMech::NONE;
        oxidationMech   x = oxidationMech::NONE;
        coagulationMech c = coagulationMech::NONE;

        SECTION("MONO") {

            sootModel SM = sootModel(psdMech::MONO, 2, n, g, x, c);

            REQUIRE(SM.psdMechanism == psdMech::MONO);
            REQUIRE(SM.psd->nMom == 2);
            REQUIRE(SM.nucleationMechanism == nucleationMech::NONE);
            REQUIRE(SM.growthMechanism == growthMech::NONE);
            REQUIRE(SM.oxidationMechanism == oxidationMech::NONE);
            REQUIRE(SM.coagulationMechanism == coagulationMech::NONE);
        }

        SECTION("LOGN") {

            sootModel SM = sootModel(psdMech::LOGN, 3, n, g, x, c);

            REQUIRE(SM.psdMechanism == psdMech::LOGN);
            REQUIRE(SM.psd->nMom == 3);
            REQUIRE(SM.nucleationMechanism == nucleationMech::NONE);
            REQUIRE(SM.growthMechanism == growthMech::NONE);
            REQUIRE(SM.oxidationMechanism == oxidationMech::NONE);
            REQUIRE(SM.coagulationMechanism == coagulationMech::NONE);
        }

        SECTION("QMOM (4 moments)") {

            sootModel SM = sootModel(psdMech::QMOM, 4, n, g, x, c);

            REQUIRE(SM.psdMechanism == psdMech::QMOM);
            REQUIRE(SM.psd->nMom == 4);
            REQUIRE(SM.nucleationMechanism == nucleationMech::NONE);
            REQUIRE(SM.growthMechanism == growthMech::NONE);
            REQUIRE(SM.oxidationMechanism == oxidationMech::NONE);
            REQUIRE(SM.coagulationMechanism == coagulationMech::NONE);
        }

        SECTION("MOMIC (5 moments)") {

            sootModel SM = sootModel(psdMech::MOMIC, 5, n, g, x, c);

            REQUIRE(SM.psdMechanism == psdMech::MOMIC);
            REQUIRE(SM.psd->nMom == 5);
            REQUIRE(SM.nucleationMechanism == nucleationMech::NONE);
            REQUIRE(SM.growthMechanism == growthMech::NONE);
            REQUIRE(SM.oxidationMechanism == oxidationMech::NONE);
            REQUIRE(SM.coagulationMechanism == coagulationMech::NONE);
        }
    }

    SECTION("PSD models with LL soot chemistry") {

        nucleationMech  n = nucleationMech::LL;
        growthMech      g = growthMech::LL;
        oxidationMech   x = oxidationMech::LL;
        coagulationMech c = coagulationMech::LL;

        SECTION("MONO") {

            sootModel SM = sootModel(psdMech::MONO, 2, n, g, x, c);

            REQUIRE(SM.psdMechanism == psdMech::MONO);
            REQUIRE(SM.psd->nMom == 2);
            REQUIRE(SM.nucleationMechanism == nucleationMech::LL);
            REQUIRE(SM.growthMechanism == growthMech::LL);
            REQUIRE(SM.oxidationMechanism == oxidationMech::LL);
            REQUIRE(SM.coagulationMechanism == coagulationMech::LL);
        }

        SECTION("LOGN") {

            sootModel SM = sootModel(psdMech::LOGN, 3, n, g, x, c);

            REQUIRE(SM.psdMechanism == psdMech::LOGN);
            REQUIRE(SM.psd->nMom == 3);
            REQUIRE(SM.nucleationMechanism == nucleationMech::LL);
            REQUIRE(SM.growthMechanism == growthMech::LL);
            REQUIRE(SM.oxidationMechanism == oxidationMech::LL);
            REQUIRE(SM.coagulationMechanism == coagulationMech::LL);
        }

        SECTION("QMOM (4 moments)") {

            sootModel SM = sootModel(psdMech::QMOM, 4, n, g, x, c);

            REQUIRE(SM.psdMechanism == psdMech::QMOM);
            REQUIRE(SM.psd->nMom == 4);
            REQUIRE(SM.nucleationMechanism == nucleationMech::LL);
            REQUIRE(SM.growthMechanism == growthMech::LL);
            REQUIRE(SM.oxidationMechanism == oxidationMech::LL);
            REQUIRE(SM.coagulationMechanism == coagulationMech::LL);
        }

        SECTION("MOMIC (5 moments)") {

            sootModel SM = sootModel(psdMech::MOMIC, 5, n, g, x, c);

            REQUIRE(SM.psdMechanism == psdMech::MOMIC);
            REQUIRE(SM.psd->nMom == 5);
            REQUIRE(SM.nucleationMechanism == nucleationMech::LL);
            REQUIRE(SM.growthMechanism == growthMech::LL);
            REQUIRE(SM.oxidationMechanism == oxidationMech::LL);
            REQUIRE(SM.coagulationMechanism == coagulationMech::LL);
        }
    }

    SECTION("PSD models with other soot chemistry") {

        SECTION("MONO: LIN, LIN, LEE_NEOH, FUCHS") {

            nucleationMech  n = nucleationMech::LIN;
            growthMech      g = growthMech::LIN;
            oxidationMech   x = oxidationMech::LEE_NEOH;
            coagulationMech c = coagulationMech::FUCHS;

            sootModel SM = sootModel(psdMech::MONO, 2, n, g, x, c);

            REQUIRE(SM.psdMechanism == psdMech::MONO);
            REQUIRE(SM.psd->nMom == 2);
            REQUIRE(SM.nucleationMechanism == nucleationMech::LIN);
            REQUIRE(SM.growthMechanism == growthMech::LIN);
            REQUIRE(SM.oxidationMechanism == oxidationMech::LEE_NEOH);
            REQUIRE(SM.coagulationMechanism == coagulationMech::FUCHS);
        }

        SECTION("LOGN: PAH, HACA, HACA, FRENK") {

            nucleationMech  n = nucleationMech::PAH;
            growthMech      g = growthMech::HACA;
            oxidationMech   x = oxidationMech::HACA;
            coagulationMech c = coagulationMech::FRENK;

            sootModel SM = sootModel(psdMech::LOGN, 3, n, g, x, c);

            REQUIRE(SM.psdMechanism == psdMech::LOGN);
            REQUIRE(SM.psd->nMom == 3);
            REQUIRE(SM.nucleationMechanism == nucleationMech::PAH);
            REQUIRE(SM.growthMechanism == growthMech::HACA);
            REQUIRE(SM.oxidationMechanism == oxidationMech::HACA);
            REQUIRE(SM.coagulationMechanism == coagulationMech::FRENK);
        }

        SECTION("QMOM 4: LL, HACA, NSC_NEOH, FUCHS") {

            nucleationMech  n = nucleationMech::LL;
            growthMech      g = growthMech::HACA;
            oxidationMech   x = oxidationMech::NSC_NEOH;
            coagulationMech c = coagulationMech::FUCHS;

            sootModel SM = sootModel(psdMech::QMOM, 4, n, g, x, c);

            REQUIRE(SM.psdMechanism == psdMech::QMOM);
            REQUIRE(SM.psd->nMom == 4);
            REQUIRE(SM.nucleationMechanism == nucleationMech::LL);
            REQUIRE(SM.growthMechanism == growthMech::HACA);
            REQUIRE(SM.oxidationMechanism == oxidationMech::NSC_NEOH);
            REQUIRE(SM.coagulationMechanism == coagulationMech::FUCHS);
        }
    }

    SECTION("sourceTerms structure initialization") {

        nucleationMech  n = nucleationMech::LL;
        growthMech      g = growthMech::LL;
        oxidationMech   x = oxidationMech::LL;
        coagulationMech c = coagulationMech::LL;

        SECTION("sootSourceTerms") {

            SECTION("MONO") {

                sootModel SM = sootModel(psdMech::MONO, 2, n, g, x, c);

                REQUIRE(SM.sourceTerms->sootSourceTerms.at(0) == 0);
                REQUIRE(SM.sourceTerms->sootSourceTerms.at(1) == 0);

            }

            SECTION("LOGN") {

                sootModel SM = sootModel(psdMech::LOGN, 3, n, g, x, c);

                REQUIRE(SM.sourceTerms->sootSourceTerms.at(0) == 0);
                REQUIRE(SM.sourceTerms->sootSourceTerms.at(1) == 0);
                REQUIRE(SM.sourceTerms->sootSourceTerms.at(2) == 0);

            }

            SECTION("QMOM (4 moments)") {

                sootModel SM = sootModel(psdMech::QMOM, 6, n, g, x, c);

                REQUIRE(SM.sourceTerms->sootSourceTerms.at(0) == 0);
                REQUIRE(SM.sourceTerms->sootSourceTerms.at(1) == 0);
                REQUIRE(SM.sourceTerms->sootSourceTerms.at(2) == 0);
                REQUIRE(SM.sourceTerms->sootSourceTerms.at(3) == 0);
                REQUIRE(SM.sourceTerms->sootSourceTerms.at(4) == 0);
                REQUIRE(SM.sourceTerms->sootSourceTerms.at(5) == 0);

            }

            SECTION("MOMIC (5 moments)") {

                sootModel SM = sootModel(psdMech::MOMIC, 5, n, g, x, c);

                REQUIRE(SM.sourceTerms->sootSourceTerms.at(0) == 0);
                REQUIRE(SM.sourceTerms->sootSourceTerms.at(1) == 0);
                REQUIRE(SM.sourceTerms->sootSourceTerms.at(2) == 0);
                REQUIRE(SM.sourceTerms->sootSourceTerms.at(3) == 0);
                REQUIRE(SM.sourceTerms->sootSourceTerms.at(4) == 0);

            }
        }

        SECTION("gasSourceTerms") {

            SECTION("MONO") {

                sootModel SM = sootModel(psdMech::MONO, 2, n, g, x, c);

                for (auto const& x : SM.sourceTerms->gasSourceTerms) {
                    gasSp sp = x.first;
                    REQUIRE(SM.sourceTerms->gasSourceTerms.at(sp) == 0);
                }
            }

            SECTION("LOGN") {

                sootModel SM = sootModel(psdMech::LOGN, 3, n, g, x, c);

                for (auto const& x : SM.sourceTerms->gasSourceTerms) {
                    gasSp sp = x.first;
                    REQUIRE(SM.sourceTerms->gasSourceTerms.at(sp) == 0);
                }
            }

            SECTION("QMOM (6 moments)") {

                sootModel SM = sootModel(psdMech::QMOM, 6, n, g, x, c);

                for (auto const& x : SM.sourceTerms->gasSourceTerms) {
                    gasSp sp = x.first;
                    REQUIRE(SM.sourceTerms->gasSourceTerms.at(sp) == 0);
                }
            }

            SECTION("MOMIC (5 moments)") {

                sootModel SM = sootModel(psdMech::MOMIC, 5, n, g, x, c);

                for (auto const& x : SM.sourceTerms->gasSourceTerms) {
                    gasSp sp = x.first;
                    REQUIRE(SM.sourceTerms->gasSourceTerms.at(sp) == 0);
                }
            }
        }

        SECTION("pahSourceTerms") {

            SECTION("MONO") {

                sootModel SM = sootModel(psdMech::MONO, 2, n, g, x, c);

                for (auto const& x : SM.sourceTerms->pahSourceTerms) {
                    pahSp sp = x.first;
                    REQUIRE(SM.sourceTerms->pahSourceTerms.at(sp) == 0);
                }
            }

            SECTION("LOGN") {

                sootModel SM = sootModel(psdMech::LOGN, 3, n, g, x, c);

                for (auto const& x : SM.sourceTerms->pahSourceTerms) {
                    pahSp sp = x.first;
                    REQUIRE(SM.sourceTerms->pahSourceTerms.at(sp) == 0);
                }
            }

            SECTION("QMOM (6 moments)") {

                sootModel SM = sootModel(psdMech::QMOM, 6, n, g, x, c);

                for (auto const& x : SM.sourceTerms->pahSourceTerms) {
                    pahSp sp = x.first;
                    REQUIRE(SM.sourceTerms->pahSourceTerms.at(sp) == 0);
                }
            }

            SECTION("MOMIC (5 moments)") {

                sootModel SM = sootModel(psdMech::MOMIC, 5, n, g, x, c);

                for (auto const& x : SM.sourceTerms->pahSourceTerms) {
                    pahSp sp = x.first;
                    REQUIRE(SM.sourceTerms->pahSourceTerms.at(sp) == 0);
                }
            }
        }
    }

}

////////////////////////////////////////////////////////////////////////////////

TEST_CASE("getSourceTermImplementation function call", "[psdModel][getSourceTerms]") {

    SECTION("MONO with NONE soot chemistry") {

        nucleationMech  n = nucleationMech::NONE;
        growthMech      g = growthMech::NONE;
        oxidationMech   x = oxidationMech::NONE;
        coagulationMech c = coagulationMech::NONE;

        vector<double> yGas = {0, 0.1, 0.1, 0.01, 0.02, 0.03, 0.04, 2E-15};        // [H, H2, O, O2, OH, H2O, CO, C2H2]
        vector<double> yPAH = {0, 0, 0, 0, 0, 0};                 // [C10H8, C12H8, C12H10, C14H10, C16H10, C18H10]
        vector<double> ySootVar{0.003, 1.5E-5};

        state S = state();
        S.setState(2100, 101325, 0.1, 1E-5, 29, yGas, yPAH, ySootVar);

        sootModel SM = sootModel(psdMech::MONO, 2, n, g, x, c);

        sourceTermStruct ST;
//        SM.psd->getSourceTermsImplementation(state,)

    }
}

////////////////////////////////////////////////////////////////////////////////

