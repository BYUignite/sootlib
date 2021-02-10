#ifndef TESTTOOLS_H
#define TESTTOOLS_H

#include "sootlib/state/gas/GasState.h"
#include "sootlib/state/soot/MomentSootState.h"

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
