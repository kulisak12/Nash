#include "matrix.h"

void Matrix::appendRow(std::vector<double>& row) {
	if (numRows == 0) {
		numColumns = row.size();
	}
	numRows++;

	m.push_back(row);
}

int Matrix::getNumRows() {
	return numRows;
}

int Matrix::getNumColumns() {
	return numColumns;
}

Matrix Matrix::transpose() {
    Matrix t;
	for (int j = 0; j < numColumns; j++) {
		std::vector<double> tRow;
		tRow.resize(numRows);
		for (int i = 0; i < numRows; i++) {
			tRow[i] = m[i][j];
		}
		t.appendRow(tRow);
	}
	return t;
}

// add a constant to all entries to make them nonnegative
// return this constant
double Matrix::normalize() {
	// get minimum
	double min = m[0][0];
	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < numColumns; j++) {
			if (m[i][j] < min) {
				min = m[i][j];
			}
		}
	}
	
	// add to all
	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < numColumns; j++) {
			m[i][j] -= min;
		}
	}

	return -min;
}