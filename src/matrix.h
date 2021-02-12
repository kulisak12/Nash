#pragma once

#include <vector>

class Matrix {
  public:
	void appendRow(std::vector<double>& row);
	void multiplyRow(int row, double coeff);
	void addRows(int source, int dest, double coeff);

	int getNumRows();
	int getNumColumns();
	std::vector<double> getRow(int row);
	std::vector<double> getColumn(int col);

	double extract(int row, int col);
	void set(int row, int col, double val);

	Matrix transpose();
	double normalize();

  private:
	int numRows = 0;
	int numColumns = 0;
    std::vector<std::vector<double>> m;
};