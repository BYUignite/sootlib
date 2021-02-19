#ifndef TESTTOOLS_H
#define TESTTOOLS_H

#include "sootlib/state/gas/GasState.h"
#include "sootlib/state/soot/MomentSootState.h"
#include "sootlib/state/soot/BinSootState.h"

class TestTools
{
public:
	[[nodiscard]] static soot::GasState getBlankGasState()
	{
		return soot::GasState();
	}

	[[nodiscard]] static soot::MomentSootState getBlankMomentSootState()
	{
		return soot::MomentSootState();
	}

	[[nodiscard]] static soot::BinSootState getBlankBinSootState()
	{
		return soot::BinSootState();
	}
};

#endif //TESTTOOLS_H
