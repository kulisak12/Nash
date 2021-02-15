#pragma once

#include <vector>

struct Equilibrium {
	std::vector<double> strategy1;
	std::vector<double> strategy2;
};

void normalizeStrategy(std::vector<double>& vec);
void printEquilibrium(Equilibrium& eq);