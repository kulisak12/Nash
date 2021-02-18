#pragma once

#include <string>

class Params {
  public:
	bool help = false;
	int num = 1;
	std::string file;
	std::string sep = " ";

	void parse(int argc, char* argv[]);
  private:
	bool longFlag(std::string& flag, std::string& nextArg);
	bool shortFlags(std::string& flag, std::string& nextArg);
};

void printHelp();
void printUsage();