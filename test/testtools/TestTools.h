#ifndef TESTTOOLS_H
#define TESTTOOLS_H

#include "sootlib/state/GasState.h"
#include "sootlib/state/MomentSootState.h"

class TestTools
{
public:
	[[nodiscard]] static soot::GasState getBlankGasState()
	{
		return soot::GasState();
	}

	[[nodiscard]] static soot::SootState getBlankSootState()
	{
		return soot::SootState();
	}
};

#endif //TESTTOOLS_H
