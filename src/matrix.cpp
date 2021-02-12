#include "matrix.h"

// * row operations

void Matrix::appendRow(std::vector<double>& row) {
	if (numRows == 0) {
		numColumns = row.size();
	}
	numRows++;

	m.push_back(row);
}

// multiply entire row by a number
void Matrix::multiplyRow(int row, double coeff) {
	for (int i = 0; i < numColumns; i++) {
		m[row][i] *= coeff;
	}
}

// add a multiple of one row to another
void Matrix::addRows(int source, int dest, double coeff) {
	for (int i = 0; i < numColumns; i++) {
		m[dest][i] += m[source][i] * coeff;
	}
}


// * getters

int Matrix::getNumRows() {
	return numRows;
}

int Matrix::getNumColumns() {
	return numColumns;
}

std::vector<double> Matrix::getRow(int row) {
	return m[row];
}

std::vector<double> Matrix::getColumn(int col) {
	std::vector<double> result;
	result.resize(numRows);
	for (int i = 0; i < numRows; i++) {
		result[i] = m[i][col];
	}
	return result;
}


// * direct access

// get value and reset to 0
double Matrix::extract(int row, int col) {
	double val = m[row][col];
	m[row][col] = 0;
	return val;
}

void Matrix::set(int row, int col, double val) {
	m[row][col] = val;
}

// * transformations

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