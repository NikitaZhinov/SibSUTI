#include "ex02.h"

#include "queue.h"
#include "stack.h"

void main_ex02() {
	std::setlocale(LC_ALL, ".UTF-8");

	std::println("-----------------Second task----------------");

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 10);

	std::println("--------------Порядок добавления------------");
	std::size_t N = dis(gen);
	queue<stack<int>> mat;
	for (std::size_t i = 0; i < N; i++) {
		std::size_t M = dis(gen);
		stack<int> arr;
		for (std::size_t i = 0; i < M; i++) {
			int elem = dis(gen);
			arr.push(elem);
			std::print("{} ", elem);
		}
		mat.push(arr);
		std::println();
	}

	std::println();
	std::println();

	std::println("---------------Порядок удаления-------------");
	while (!mat.empty()) {
		auto arr = mat.front();
		while (!arr.empty()) {
			std::print("{} ", arr.top());
			arr.pop();
		}
		std::println();
		mat.pop();
	}
}
