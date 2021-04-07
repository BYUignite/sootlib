#ifndef TESTTOOLS_H
#define TESTTOOLS_H

#include "sootlib/state/State.h"

using namespace soot;
using namespace std;

class TestTools
{
public:
	[[nodiscard]] static State getBlankState() {
	    return State();
	}
};

#endif //TESTTOOLS_H
