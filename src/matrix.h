#pragma once

#include <vector>

class Matrix {
  public:
	void appendRow(std::vector<double>& row);
	int getNumRows();
	int getNumColumns();
	Matrix transpose();
	double normalize();
  private:
	int numRows = 0;
	int numColumns = 0;
    std::vector<std::vector<double>> m;
};