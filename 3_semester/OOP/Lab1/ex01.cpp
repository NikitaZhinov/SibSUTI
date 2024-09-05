#include "ex01.h"

void main_ex01() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 10);

	int size = dis(gen);
	int maxValue = 100;
	int* arr = genRandArray(size, maxValue);

	std::println("-----------------First task-----------------");
	print(arr);
	std::println("");

	delete[] arr;
}

int* genRandArray(int size, int maxValue) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, maxValue);

	int* arr = new int[size + 1];
	arr[0] = size;
	for (std::size_t i = 1; i <= size; i++)
		arr[i] = dis(gen);
	return arr;
}

void print(int* arr) {
	std::print("{}: ", arr[0]);
	for (std::size_t i = 1; i <= arr[0]; i++)
		std::print("{} ", arr[i]);
	std::println("");
}
