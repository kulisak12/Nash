#include <iostream>
#include "params.h"
#include "reader.h"
#include "matrix.h"

Matrix loadMatrix(Reader& reader);
void assertDimensions(Matrix& m1, Matrix& m2);

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
	Matrix payoff1, payoff2;
	Reader reader;
	try {
		reader.open(params.file, params.sep);
		payoff1 = loadMatrix(reader);
		payoff2 = loadMatrix(reader);
		assertDimensions(payoff1, payoff2);
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		reader.close();
		return 1;
	}
	reader.close();
	payoff2 = payoff2.transpose();
	payoff1.normalize();
	payoff2.normalize();

	return 0;
}

// make sure all rows have the same number of entires
void assertLineLength(int extraEntries, std::string errorPrefix) {
	if (extraEntries == 0) {
		return;
	}

	throw std::runtime_error("nash: " + errorPrefix +
		"wrong number of entries, expected " +
		std::to_string(abs(extraEntries)) +
		(extraEntries < 0 ? " more" : " less"));
}

// use data from reader to construct a matrix
Matrix loadMatrix(Reader& reader) {
	Matrix m;
	int lineLength = reader.nextLineLength();
	while (lineLength > 0) {
		// construct row
		std::vector<double> row;
		row.resize(lineLength);
		for (int i = 0; i < lineLength; i++) {
			row[i] = reader.next();
		}
		m.appendRow(row);

		assertLineLength(lineLength - m.getNumColumns(), reader.errorPrefix(true));
		lineLength = reader.nextLineLength();
	}
	return m;
}

void assertDimensions(Matrix& m1, Matrix& m2) {
	if (m1.getNumRows() == 0) {
		throw std::runtime_error("nash: matrix 1 is empty");
	}
	if (m2.getNumRows() == 0) {
		throw std::runtime_error("nash: matrix 2 is empty");
	}
	if (m1.getNumRows() != m2.getNumRows() ||
		m1.getNumColumns() != m2.getNumColumns()) {
		throw std::runtime_error("nash: unmatching matrix dimensions");
	}
}