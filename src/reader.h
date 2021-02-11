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
	std::string errorPrefix(bool includeLineNumber);

  private:
	bool loadNextLine();
	double parseDouble(std::string& str);
	int nextSepPos(std::string& str, int begin);
	std::string sep;
	std::string fileName;
	std::ifstream inputFile;
	std::vector<std::string> lineSplits;
	int nextIndex;
	int lineNumber = 0;
};