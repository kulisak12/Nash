#pragma once

#include "equilibrium.h"
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

Equilibrium lemkeHowson(Matrix& payoff1, Matrix& payoff2, int startLabel);