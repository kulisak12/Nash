#include <cmath>
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
	int multiple = power(10, places);
	return std::round(x * multiple) / multiple;
}
