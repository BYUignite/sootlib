#include <memory>

#include "gtest/gtest.h"

#include "TestTools.h"

TEST (OxidationModel_NSC_NEOH_TEST, zero_test)
{
	auto model = std::make_unique<soot::OxidationModel_NSC_NEOH>();

	auto gasState = TestTools::getBlankGasState();
	auto sootState = TestTools::getBlankMomentSootState();

	const double expected_value = 0.0;

	ASSERT_FLOAT_EQ (expected_value, model->getOxidationRate(gasState, sootState));
}

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
