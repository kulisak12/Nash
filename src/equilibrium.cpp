#include <iostream>
#include <sstream>

#include "equilibrium.h"
#include "utility.h"

// scale such that entries sum up to 1
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

// get a string representation of vector
std::string formatVector(std::vector<double>& vec) {
	std::ostringstream result;
	for (int i = 0; i < vec.size(); i++) {
		result << vec[i];
		if (i < vec.size() - 1) {
			result << ", ";
		}
	}
	return result.str();
}

void printEquilibrium(Equilibrium& eq) {
	std::cout << "x = (" << formatVector(eq.strategy1) <<
		"), y = (" << formatVector(eq.strategy2) << ")" << std::endl;
}

// round all numbers in a vector
void roundVector(std::vector<double>& vec, int places) {
	for (int i = 0; i < vec.size(); i++) {
		vec[i] = round(vec[i], places);
	}
}

// check if equilibria are the same
bool equilibriaMatch(Equilibrium& eq1, Equilibrium& eq2) {
	return eq1.strategy1 == eq2.strategy1 && eq1.strategy2 == eq2.strategy2;
}