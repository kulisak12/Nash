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

std::string formatVector(std::vector<double>& vec) {
	const int precision = 3;
	std::ostringstream result;

	for (int i = 0; i < vec.size(); i++) {
		result << round(vec[i], precision);
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