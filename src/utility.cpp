#include <cmath>
#include <iostream>
#include <string>
#include <vector>

std::string quote(std::string text) {
	return "'" + text + "'";
}

const double eps = 1E-10;

bool isZero(double x) {
	return (-eps < x && x < eps);
}

int power(int base, int exp) {
	int result = 1;
	for (int i = 0; i < exp; i++) {
		result *= base;
	}
	return result;
}

double round(double x, int places) {
	int multiple = power(10, 2);
	return std::floor(x * multiple) / multiple;
}

void printVector(std::vector<double>& vec) {
	const int precision = 2;
	for (int i = 0; i < vec.size(); i++) {
		std::cout << round(vec[i], precision);
		if (i < vec.size() - 1) {
			std::cout << ", ";
		}
	}
}