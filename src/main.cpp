#include <iostream>
#include "params.h"
#include "reader.h"

int main(int argc, char* argv[]) {
	// parse parameters
	Params params;
	try {
		params.parse(argc, argv);
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		printUsage();
		return 1;
	}
	if (params.help) {
		printHelp();
		return 0;
	}
	
	// load input
	Reader reader;
	try {
		reader.open(params.file, params.sep);
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	
	return 0;
}