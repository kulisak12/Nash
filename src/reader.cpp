#include <iostream>
#include <sstream>
#include "reader.h"
#include "utility.h"

void Reader::open(std::string& fileName, std::string& sep) {
	this->fileName = fileName;
	this->sep = sep;

	if (fileName != "") {
		inputFile.open(fileName, std::ios::in);
		if (!inputFile.is_open()) {
			throw std::runtime_error("Error opening file");
		}
		// redirect file to standard input
		std::cin.rdbuf(inputFile.rdbuf());
	}
	// if fileName == "", keep standard input
}

void Reader::close() {
	if (inputFile.is_open()) {
		inputFile.close();
	}
}

int Reader::nextSepPos(std::string& str, int start) {
	if (sep == " ") {
		// whitespace
		return str.find_first_of(" \t\v", start);
	}
	else {
		// custom string
		return str.find(sep, start);
	}
}

// read next line, split and store to buffer
bool Reader::loadNextLine() {
	lineSplits.clear();
	nextIndex = 0;
	lineNumber++;

	std::string line;
	if(!std::getline(std::cin, line)) {
		return false;
	}

	// split by sep
	int start = 0;
	int sepPos;
	while (sepPos != std::string::npos) {
		// find first non-sep char
		sepPos = nextSepPos(line, start);
		while (sepPos == start && sepPos != std::string::npos) {
			start += sep.length();
			sepPos = nextSepPos(line, start);
		}
		// add entry
		if (start != line.size()) {
			lineSplits.push_back(line.substr(start, sepPos - start));
			start = sepPos + sep.length();
		}
	}
	return true;
}

// number of entries on line
// returns -1 if no next line exists
int Reader::nextLineLength() {
	bool hasNextLine = loadNextLine();
	if (hasNextLine) {
		return lineSplits.size();
	}
	else {
		return -1;
	}
}

double parseDouble(std::string& str) {
    double d;
    if (!(std::istringstream(str) >> d >> std::ws).eof()) { // magic
		throw std::runtime_error("nash: invalid number argument " + quote(str));
	}
	return d;
}

// get next matrix entry
double Reader::next() {
	// load next line if necessary
	while (nextIndex == lineSplits.size()) {
		loadNextLine(); // resets nextIndex
	}

	double entry = parseDouble(lineSplits[nextIndex]);
	nextIndex++;
	return entry;
}

// generate prefix in form of file:line
// empty if reading from standard input
std::string Reader::errorPrefix(bool includeLineNumber) {
	if (fileName == "") {
		return "";
	}
	else if (includeLineNumber) {
		return fileName + ":" + std::to_string(lineNumber) + " ";
	}
	else {
		return fileName + " ";
	}
}