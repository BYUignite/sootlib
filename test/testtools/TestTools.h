#ifndef TESTTOOLS_H
#define TESTTOOLS_H

#include "sootlib/state/InputState.h"

using namespace soot;
using namespace std;

class TestTools
{
public:
	[[nodiscard]] static InputState getBlankState() {
	    return InputState();
	}
};

#endif //TESTTOOLS_H
