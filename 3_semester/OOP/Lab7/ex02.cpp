#include "ex02.h"

void main_ex02() {
	std::println("-----------------Second task----------------");

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 10);

	list<list<int>> mat(dis(gen));
	for (auto& arr : mat) {
		arr = list<int>(dis(gen));
		for (int& elem : arr) {
			elem = dis(gen);
			std::print("{} ", elem);
		}
		std::println();
	}
}
