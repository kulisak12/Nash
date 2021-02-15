#pragma once

#include <vector>

struct Equilibrium {
	std::vector<double> strategy1;
	std::vector<double> strategy2;
};

void normalizeStrategy(std::vector<double>& vec);
void printEquilibrium(Equilibrium& eq);
void roundVector(std::vector<double>& vec, int places);
bool equilibriaMatch(Equilibrium& eq1, Equilibrium& eq2);