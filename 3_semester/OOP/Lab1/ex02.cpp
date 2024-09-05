#include "ex02.h"

void main_ex02() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 10);

	int size = dis(gen);
	int maxValue = 100;
	int** matrix = genRandMatrix(size, maxValue);
	
	std::println("-----------------Second task----------------");
	print(matrix);
	std::println("");

	for (std::size_t i = 1; i <= matrix[0][0]; i++)
		delete[] matrix[i];
	delete[] matrix;
}

int** genRandMatrix(int size, int maxValue) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 10);

	int** matrix = new int*[size + 1];
	matrix[0] = new int[1];
	matrix[0][0] = size;
	for (std::size_t i = 1; i <= matrix[0][0]; i++)
		matrix[i] = genRandArray(dis(gen), maxValue);
	return matrix;
}

void printMatrix(int** matrix) {
	std::println("{}", matrix[0][0]);
	for (std::size_t i = 1; i <= matrix[0][0]; i++)
		print(matrix[i]);
}

void print(int** matrix) {
	printMatrix(matrix);
}
