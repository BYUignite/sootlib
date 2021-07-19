#include <catch2/catch.hpp>

#include "state.h"

using namespace std;
using namespace soot;

////////////////////////////////////////////////////////////////////////////////

TEST_CASE("state object initialization with default values", "[state]") {

    state S = state();

    REQUIRE(S.T == 0);
    REQUIRE(S.P == 0);
    REQUIRE(S.rhoGas == 0);
    REQUIRE(S.MWGas == 0);
    REQUIRE(S.muGas == 0);
    REQUIRE(S.cMin == 100);

    // sample gasFractions map
    REQUIRE(S.gasFractions.at(gasSp::C2H2) == 0);
    REQUIRE(S.gasFractions.at(gasSp::H2O) == 0);
    REQUIRE(S.gasFractions.at(gasSp::CO) == 0);

    // sample pahFractions map
    REQUIRE(S.pahFractions.at(pahSp::C10H8) == 0);
    REQUIRE(S.pahFractions.at(pahSp::C12H10) == 0);
    REQUIRE(S.pahFractions.at(pahSp::C16H10) == 0);

    // check sootVar
    REQUIRE(S.sootVar.empty());

}

////////////////////////////////////////////////////////////////////////////////

TEST_CASE("setState function call with 'good' values", "[state][setState]") {

    state S = state();

    vector<double> yGas = {0, 0.1, 0.1, 0.01, 0.02, 0.03, 0.04, 0.2};   // [H, H2, O, O2, OH, H2O, CO, C2H2]
    vector<double> yPAH = {0, 0.1, 0.1, 0.01, 0.02, 0};                 // [C10H8, C12H8, C12H10, C14H10, C16H10, C18H10]
    vector<double> ySootVar{0.003, 1.5E-5};

    S.setState(2500, 101325, 0.1, 0.5, 29, yGas, yPAH, ySootVar, 150);

    SECTION("correct values are assigned to scalar variables") {
        REQUIRE(S.T == 2500);
        REQUIRE(S.P == 101325);
        REQUIRE(S.rhoGas == 0.1);
        REQUIRE(S.muGas == 0.5);
        REQUIRE(S.MWGas == 29);
        REQUIRE(S.cMin == 150);
    }

    SECTION("gas and PAH mass fractions are assigned correctly") {
        REQUIRE(S.gasFractions.at(gasSp::H) == 0);
        REQUIRE(S.gasFractions.at(gasSp::C2H2) == 0.2);
        REQUIRE(S.gasFractions.at(gasSp::H2O) == 0.03);
        REQUIRE(S.pahFractions.at(pahSp::C12H8) == 0.1);
        REQUIRE(S.pahFractions.at(pahSp::C16H10) == 0.02);
    }

    SECTION("sootVar is resized properly with correct values") {
        REQUIRE(S.sootVar.size() == 2);
        REQUIRE(S.sootVar.at(0) == 0.003);
        REQUIRE(S.sootVar.at(1) == 1.5E-5);
    }

    SECTION("on subsequent function calls") {

        vector<double> yGas2 = {0.5, 0.001, 0.12, 0.24, 0.02, 0, 0, 0.02};   // [H, H2, O, O2, OH, H2O, CO, C2H2]
        vector<double> yPAH2 = {0.003, 0.01, 0.1, 0.1, 0.0002, 0.25};          // [C10H8, C12H8, C12H10, C14H10, C16H10, C18H10]
        vector<double> ySootVar2{0.1, 1.4E-3, 0.0006};

        S.setState(1234, 101325, 0.01, 0.006, 29, yGas2, yPAH2, ySootVar2, 150);

        SECTION("old scalar values do not persist") {
            REQUIRE(S.T == 1234);
            REQUIRE(S.rhoGas == 0.01);
            REQUIRE(S.muGas == 0.006);
        }

        SECTION("old gas and PAH mass fraction values do not persist") {
            REQUIRE(S.gasFractions.at(gasSp::H) == 0.5);
            REQUIRE(S.gasFractions.at(gasSp::C2H2) == 0.02);
            REQUIRE(S.gasFractions.at(gasSp::H2O) == 0);
            REQUIRE(S.pahFractions.at(pahSp::C12H8) == 0.01);
            REQUIRE(S.pahFractions.at(pahSp::C16H10) == 0.0002);
        }

        SECTION("sootVar sized correctly and old sootVar values do not persist") {
            REQUIRE(S.sootVar.size() == 3);
            REQUIRE(S.sootVar.at(0) == 0.1);
            REQUIRE(S.sootVar.at(1) == 1.4E-3);
            REQUIRE(S.sootVar.at(2) == 0.0006);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_CASE("setState function call with 'bad' values", "[state][setState]") {

    state S = state();

    vector<double> yGas0 = {0, 0, 0, 0, 0, 0, 0, 0};   // [H, H2, O, O2, OH, H2O, CO, C2H2]
    vector<double> yPAH0 = {0, 0, 0, 0, 0, 0};                 // [C10H8, C12H8, C12H10, C14H10, C16H10, C18H10]
    vector<double> ySootVar0{0, 0};

    SECTION("negative or zero values for scalar variables throw errors") {

        double T = 0;
        double P = -101325;
        double rhoGas = -0.5;
        double muGas = -0.001;
        double MWGas = 0;
        double cMin = -2;

        REQUIRE_THROWS(S.setState(T,    101325, 0.1,    0.5,   29,    yGas0, yPAH0, ySootVar0, 100));
        REQUIRE_THROWS(S.setState(2500, P,      0.1,    0.5,   29,    yGas0, yPAH0, ySootVar0, 100));
        REQUIRE_THROWS(S.setState(2500, 101325, rhoGas, 0.5,   29,    yGas0, yPAH0, ySootVar0, 100));
        REQUIRE_THROWS(S.setState(2500, 101325, 0.1,    muGas, 29,    yGas0, yPAH0, ySootVar0, 100));
        REQUIRE_THROWS(S.setState(2500, 101325, 0.1,    0.5,   MWGas, yGas0, yPAH0, ySootVar0, 100));
        REQUIRE_THROWS(S.setState(2500, 101325, 0.1,    0.5,   29,    yGas0, yPAH0, ySootVar0, cMin));
    }

    SECTION("negative values for gas/PAH mass fractions and soot moments/bins throw errors") {

        vector<double> yGas = {0, 0, -0.02, 0, 0, 0, 0, 0};
        vector<double> yPAH = {0, 0, 0, 0, 0, -0.0001};
        vector<double> ySootVar{0, 0, -0.0005};

        REQUIRE_THROWS(S.setState(2500, 101325, 0.1,    0.5,   29,    yGas, yPAH0, ySootVar0, 100));
        REQUIRE_THROWS(S.setState(2500, 101325, 0.1,    0.5,   29,    yGas0, yPAH, ySootVar0, 100));
        REQUIRE_THROWS(S.setState(2500, 101325, 0.1,    0.5,   29,    yGas0, yPAH0, ySootVar, 100));

    }

    SECTION("values >1 for gas/PAH mass fractions throw errors") {

        vector<double> yGas = {1.1, 0, 0, 0, 0, 0, 0, 0};
        vector<double> yPAH = {0, 0, 0, 0, 1.2E2, 0};

        REQUIRE_THROWS(S.setState(2500, 101325, 0.1,    0.5,   29,    yGas, yPAH0, ySootVar0, 100));
        REQUIRE_THROWS(S.setState(2500, 101325, 0.1,    0.5,   29,    yGas0, yPAH, ySootVar0, 100));

    }

    SECTION("incorrect vector size for gas/PAH mass fractions throws error") {

        vector<double> yGas = {0, 0, 0, 0, 0, 0};       // 2 too few elements
        vector<double> yPAH = {0, 0, 0, 0, 0, 0, 0};    // 1 too many elements

        REQUIRE_THROWS(S.setState(2500, 101325, 0.1,    0.5,   29,    yGas, yPAH0, ySootVar0, 100));
        REQUIRE_THROWS(S.setState(2500, 101325, 0.1,    0.5,   29,    yGas0, yPAH, ySootVar0, 100));

    }
}

////////////////////////////////////////////////////////////////////////////////

//TEST_CASE("get gas/PAH C/P/N function calls", "[state]") {
//
//    state S = state();
//
//
//}

////////////////////////////////////////////////////////////////////////////////

TEST_CASE("getParticleCollisionRate function call", "[state]") {

    state S = state();

    SECTION("throws error if state variables have not been set"){
        REQUIRE_THROWS(S.getParticleCollisionRate(1,4));
        REQUIRE_THROWS(S.getParticleCollisionRate(12,45));
    }

    vector<double> yGas0 = {0, 0, 0, 0, 0, 0, 0, 0};   // [H, H2, O, O2, OH, H2O, CO, C2H2]
    vector<double> yPAH0 = {0, 0, 0, 0, 0, 0};                 // [C10H8, C12H8, C12H10, C14H10, C16H10, C18H10]
    vector<double> ySootVar0{0, 0};

    S.setState(2500, 101325, 0.1, 0.5, 29, yGas0, yPAH0, ySootVar0, 150);

    SECTION("handles negative and/or zero input values") {
        REQUIRE_THROWS(S.getParticleCollisionRate(-0.2,4));
        REQUIRE_THROWS(S.getParticleCollisionRate(0.5,0));
        REQUIRE_THROWS(S.getParticleCollisionRate(0,0));
    }

    SECTION("returns valid values of collision rate function beta in m3/#*s") {
        REQUIRE(S.getParticleCollisionRate(12,55) >= 0);
        REQUIRE(S.getParticleCollisionRate(0.002,0.05) >= 0);
        REQUIRE(S.getParticleCollisionRate(0.1,45) >= 0);
    }


}