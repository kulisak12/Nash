#include "lemke-howson.h"

void normalizeStrategy(std::vector<double>& vec) {
	double sum = 0;
	for (int i = 0; i < vec.size(); i++) {
		sum += vec[i];
	}

	double coeff = 1 / sum;
	for (int i = 0; i < vec.size(); i++) {
		vec[i] *= coeff;
	}
}

Equilibrium lemkeHowson(Matrix& payoff1, Matrix& payoff2, int startLabel) {
	Pivoting p1(payoff1, 1);
	Pivoting p2(payoff2, 2);
	int numActions1 = payoff1.getNumRows();

	// perform pivoting
	int labelDropped = startLabel;
	do {
		// drop one label, take another one
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