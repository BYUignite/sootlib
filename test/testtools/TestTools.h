#ifndef TESTTOOLS_H
#define TESTTOOLS_H

#include <fstream>
#include <iostream>

class TestTools
{
public:
	/*
	 * function to get an out stream from either no or one arguments
	 *
	 * will leak an ofstream to memory everytime called to make a file stream
	 * (do not call excessively to make new file streams)
	 */
	static std::ostream* getOutStreamFromArgs(int argc, char** argv) {
		if (argc == 1) {
			return &std::cout;
		}
		else if (argc == 2) {
			auto* out = new std::ofstream();
			out->open(argv[1]);
			return out;
		}
		else {
			std::cerr << "Provide no arguments to print to console or 1 argument to print to a file" << std::endl;
			exit(1);
		}
	}
};

#endif //TESTTOOLS_H
