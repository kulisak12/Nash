#pragma once

#include <fstream>
#include <string>
#include <vector>

class Reader {
  public:
	void open(std::string& fileName, std::string& sep);
	void close();
	int nextLineLength();
	double next();

  private:
	bool loadNextLine();
	int nextSepPos(std::string& str, int begin);
	std::string sep;
	std::ifstream inputFile;
	std::vector<std::string> lineSplits;
	int nextIndex;
};