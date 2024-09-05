#include "ex02.h"

void main_ex02() {
	std::println("-----------------Second task----------------");

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 10);

	int n = dis(gen);
	int** mat = new int* [n];
	for (int i = 0; i < n; i++) {
		int m = dis(gen);
		mat[i] = new int[m];
		for (int j = 0; j < m; j++) {
			mat[i][j] = dis(gen);
			std::print("{} ", mat[i][j]);
		}
		std::println();
	}

	for (int i = 0; i < n; i++) delete[] mat[i];
	delete[] mat;
}
