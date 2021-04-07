#include <memory>

#include "gtest/gtest.h"

#include "TestTools.h"

#include "sootlib/nucleation_model/NucleationModel_NONE.h"

TEST (NucleationModel_NONE_TEST, basic_test)
{
    const State inputState = TestTools::getBlankState();
	unique_ptr<NucleationModel> model = make_unique<NucleationModel_NONE>();

	// Using exact comparison since model should return exactly 0
    const double expectedValue = 0;
    EXPECT_EQ (expectedValue, model->getNucleationRate(inputState, {}, {}));
}

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
