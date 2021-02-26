#include <memory>

#include "gtest/gtest.h"

#include "TestTools.h"

TEST (GasState_TEST, init_test)
{
	auto gasState = soot::State();

	const double expected_value = 0;

	ASSERT_EQ (expected_value, gasState.getT());
	ASSERT_EQ (expected_value, gasState.getP());
	ASSERT_EQ (expected_value, gasState.getGasRho());
	ASSERT_EQ (expected_value, gasState.getMw());
	ASSERT_EQ (expected_value, gasState.getMu());

	ASSERT_EQ (expected_value, gasState.getC2H2Frac());
	ASSERT_EQ (expected_value, gasState.getO2Frac());
	ASSERT_EQ (expected_value, gasState.getHFrac());
	ASSERT_EQ (expected_value, gasState.getH2Frac());
	ASSERT_EQ (expected_value, gasState.getOHFrac());
	ASSERT_EQ (expected_value, gasState.getH2OFrac());
	ASSERT_EQ (expected_value, gasState.getCOFrac());
	ASSERT_EQ (expected_value, gasState.getElementalCFrac());
	ASSERT_EQ (expected_value, gasState.getElementalHFrac());

	ASSERT_EQ (expected_value, gasState.getC_C2H2());
	ASSERT_EQ (expected_value, gasState.getC_O2());
	ASSERT_EQ (expected_value, gasState.getC_H());
	ASSERT_EQ (expected_value, gasState.getC_H2());
	ASSERT_EQ (expected_value, gasState.getC_OH());
	ASSERT_EQ (expected_value, gasState.getC_H2O());
	ASSERT_EQ (expected_value, gasState.getC_CO());
	ASSERT_EQ (expected_value, gasState.getC_elementalC());
	ASSERT_EQ (expected_value, gasState.getC_elementalH());

	ASSERT_EQ (expected_value, gasState.getP_C2H2());
	ASSERT_EQ (expected_value, gasState.getP_O2());
	ASSERT_EQ (expected_value, gasState.getP_H());
	ASSERT_EQ (expected_value, gasState.getP_H2());
	ASSERT_EQ (expected_value, gasState.getP_OH());
	ASSERT_EQ (expected_value, gasState.getP_H2O());
	ASSERT_EQ (expected_value, gasState.getP_CO());
	ASSERT_EQ (expected_value, gasState.getP_elementalC());
	ASSERT_EQ (expected_value, gasState.getP_elementalH());

	// FIXME I am not sure that this should come out to 0 in the beginning
	ASSERT_EQ (expected_value, gasState.getGasMeanFreePath());

	ASSERT_EQ (expected_value, gasState.getNumPAH());
}

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
