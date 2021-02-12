#pragma once

#include "matrix.h"

class Pivoting {
  public:
	Pivoting(Matrix& payoff, int player);
	int traverseEdge(int labelDropped);
	std::vector<double> getStrategy();
  private:
	Matrix m;
	std::vector<int> basis;
	int player;
};

struct Equilibrium {
	std::vector<double> strategy1;
	std::vector<double> strategy2;
};

void normalizeStrategy(std::vector<double>& vec);
Equilibrium lemkeHowson(Matrix& payoff1, Matrix& payoff2, int startLabel);
void printEquilibrium(Equilibrium& eq);