#include <limits>

#include "lemke-howson.h"
#include "utility.h"

Equilibrium lemkeHowson(Matrix& payoff1, Matrix& payoff2, int startLabel) {
	Pivoting p1(payoff1, 1);
	Pivoting p2(payoff2, 2);
	int numActions1 = payoff1.getNumRows();

	// perform pivoting
	int labelDropped = startLabel;
	do {
		if (labelDropped > numActions1) {
			labelDropped = p1.traverseEdge(labelDropped);
		}
		else {
			labelDropped = p2.traverseEdge(labelDropped);
		}
	} while (labelDropped != startLabel);

	// return answer
	Equilibrium eq;
	eq.strategy1 = p2.getStrategy(); // yes, that's the right way around
	eq.strategy2 = p1.getStrategy();
	normalizeStrategy(eq.strategy1);
	normalizeStrategy(eq.strategy2);
	return eq;
}

// initialize matrix and basis
/* matrix format is as follows:
   p1:
    basis     slack     payoff1
    --      ----------  ------
    r1 = 1  r1  r2  r3  y4  y5
    r2 = 1  r1  r2  r3  y4  y5
    r3 = 1  r1  r2  r3  y4  y5

   p2:
    basis    payoff2    slack
    --      ----------  ------
    s4 = 1  x1  x2  x3  s4  s5
    s5 = 1  x1  x2  x3  s4  s5

   basis is stored with indexes, matches column index
*/
Pivoting::Pivoting(Matrix& payoff, int player) {
	this->player = player;
	int basisSize = payoff.getNumRows();
	int numActions = payoff.getNumColumns();
	int numVariables = basisSize + numActions + 1;
	int copyOffset = (player == 1) ? basisSize + 1 : 1;

	// matrix
	for (int i = 0; i < basisSize; i++) {
		std::vector<double> row(numVariables, 0);
		row[0] = 1; // constant term
		// copy payoffs
		std::vector<double> payoffRow = payoff.getRow(i);
		for (int j = 0; j < payoffRow.size(); j++) {
			row[j + copyOffset] = -payoffRow[j];
		}
		m.appendRow(row);
	}

	// basis
	basis.resize(basisSize);
	int basisOffset = (player == 1) ? 1 : numActions + 1;
	for (int i = 0; i < basisSize; i++) {
		basis[i] = i + basisOffset;
	}
}

// minimum ratio test
int minRatio(std::vector<double>& labelColumn, std::vector<double>& constants) {
	int minRow;
	double min = std::numeric_limits<double>::max();

	for (int i = 0; i < labelColumn.size(); i++) {
		if (labelColumn[i] < 0 && !isZero(labelColumn[i])) {
			double ratio = -constants[i] / labelColumn[i];
			if (ratio < min) {
				min = ratio;
				minRow = i;
			}
		}
	}
	return minRow;
}

// drop one label, take another one
// return taken label
int Pivoting::traverseEdge(int labelDropped) {
	std::vector<double> labelColumn = m.getColumn(labelDropped);
	std::vector<double> constants = m.getColumn(0);
	int minRow = minRatio(labelColumn, constants);
	int labelTaken = basis[minRow];

	// swap basic and nonbasic variable
	m.set(minRow, labelTaken, -1);
	basis[minRow] = labelDropped;
	double enteringVal = m.extract(minRow, labelDropped);
	m.multiplyRow(minRow, -1 / enteringVal);

	// substitute to other rows
	for (int i = 0; i < labelColumn.size(); i++) {
		double coeff = m.extract(i, labelDropped);
		if (!isZero(coeff)) {
			m.addRows(minRow, i, coeff);
		}
	}

	return labelTaken;
}

std::vector<double> Pivoting::getStrategy() {
	int numActions = m.getNumColumns() - m.getNumRows() - 1;
	int actionOffset = (player == 1) ? basis.size() + 1 : 1;
	std::vector<double> constants = m.getColumn(0);
	std::vector<double> strategy;
	strategy.resize(numActions);

	// if basis contains an action variable, get its corresponding value
	for (int i = 0; i < basis.size(); i++) {
		int action = basis[i] - actionOffset;
		if (0 <= action && action < numActions) {
			strategy[action] = constants[i];
		}
	}

	return strategy;
}