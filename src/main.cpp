#include <iostream>

#include "lemke-howson.h"
#include "matrix.h"
#include "params.h"
#include "reader.h"

Matrix loadMatrix(Reader& reader);
void assertDimensions(Matrix& m1, Matrix& m2);
void repeatLemkeHowson(Matrix& payoff1, Matrix& payoff2, int desiredNumEq);

const int eqPrecision = 3;

int main(int argc, char* argv[]) {
	// parse parameters
	Params params;
	try {
		params.parse(argc, argv);
	}
	catch (const std::exception& e) {
		std::cerr << "nash: " << e.what() << std::endl;
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
		std::cerr << "nash: " << e.what() << std::endl;
		reader.close();
		return 1;
	}
	reader.close();
	payoff2 = payoff2.transpose();
	payoff1.normalize();
	payoff2.normalize();
	
	// find equilibria
	if (params.all) {
		// support enumeration
		std::cerr << "nash: Not implemented yet" << std::endl;
		return 1;
	}
	else {
		repeatLemkeHowson(payoff1, payoff2, params.num);
	}

	return 0;
}

// make sure all rows have the same number of entires
void assertLineLength(int extraEntries, std::string errorPrefix) {
	if (extraEntries == 0) {
		return;
	}

	throw std::runtime_error(errorPrefix +	"Wrong number of entries, expected " +
		std::to_string(abs(extraEntries)) +	(extraEntries < 0 ? " more" : " less"));
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
		throw std::runtime_error("Matrix 1 is empty");
	}
	if (m2.getNumRows() == 0) {
		throw std::runtime_error("Matrix 2 is empty");
	}
	if (m1.getNumRows() != m2.getNumRows() ||
		m1.getNumColumns() != m2.getNumColumns()) {
		throw std::runtime_error("Unmatching matrix dimensions");
	}
}

// run Lemke-Howson multiple times with different start labels
void repeatLemkeHowson(Matrix& payoff1, Matrix& payoff2, int desiredNumEq) {
	int totalActions = payoff1.getNumRows() + payoff1.getNumColumns();
	std::vector<Equilibrium> eqFound;

	for (int label = 1; label <= totalActions; label++) {
		// run Lemke-Howson
		Equilibrium eq = lemkeHowson(payoff1, payoff2, label);
		roundVector(eq.strategy1, eqPrecision);
		roundVector(eq.strategy2, eqPrecision);

		// compare to previously found equilibria
		bool duplicate = false;
		for (int j = 0; j < eqFound.size(); j++) {
			if (equilibriaMatch(eq, eqFound[j])) {
				duplicate = true;
				break;
			}
		}
		// new equilibrium
		if (!duplicate) {
			eqFound.push_back(eq);
			printEquilibrium(eq);
			// desired number of equilibria already found
			if (eqFound.size() == desiredNumEq) {
				return;
			}
		}
	}

	// not enough equilibria found
	std::cerr << "nash: Found only " << eqFound.size() <<
		" equilibri" << (eqFound.size() == 1 ? "um" : "a" ) << std::endl;
}