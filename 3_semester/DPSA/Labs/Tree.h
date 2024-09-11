#pragma once

#include <print>

template <class T>
struct BTreeNode {
	T value;
	BTreeNode* left, * right;

	BTreeNode(const T& val) : value(val), left(nullptr), right(nullptr) {}
};

template <class T>
class BTree {
	BTreeNode<T>* root;

	void removeBranch(BTreeNode<T>* p) {
		if (p != nullptr) {
			if (p->left != nullptr)
				removeBranch(p->left);
			if (p->right != nullptr)
				removeBranch(p->right);
			delete p;
		}
	}

	void printFromUpToDown(BTreeNode<T>* p) {
		if (p != nullptr) {
			std::print("{} ", p->value);
			printFromUpToDown(p->left);
			printFromUpToDown(p->right);
		}
	}

	void printFromLeftToRight(BTreeNode<T>* p) {
		if (p != nullptr) {
			printFromLeftToRight(p->left);
			std::print("{} ", p->value);
			printFromLeftToRight(p->right);
		}
	}

	void printFromDownToUp(BTreeNode<T>* p) {
		if (p != nullptr) {
			printFromDownToUp(p->left);
			printFromDownToUp(p->right);
			std::print("{} ", p->value);
		}
	}

	std::size_t getSize(BTreeNode<T>* p) {
		if (p == nullptr)
			return 0;
		return 1 + getSize(p->left) + getSize(p->right);
	}

	std::size_t getHeight(BTreeNode<T>* p) {
		if (p == nullptr)
			return 0;
		return std::max(getHeight(p->left), getHeight(p->right)) + 1;
	}

	std::size_t getSumLenght(BTreeNode<T>* p, std::size_t l) {
		if (p == nullptr)
			return 0;
		return l + getSumLenght(p->left, l + 1) + getSumLenght(p->right, l + 1);
	}

public:
	BTree() : root(nullptr) {}

	~BTree() {
		clear();
	}

	void add(const T& val) {
		if (root == nullptr)
			root = new BTreeNode(val);
		else {
			BTreeNode<T>* cur = root, * pred = nullptr;

			do {
				pred = cur;
				if (val < cur->value)
					cur = cur->left;
				else
					cur = cur->right;
			} while (cur != nullptr);

			if (val < pred->value)
				pred->left = new BTreeNode(val);
			else
				pred->right = new BTreeNode(val);
		}
	}

	void remove(const T& val) {
		if (root == nullptr)
			return;

		BTreeNode<T>* cur = root, * prev = nullptr;

		while (cur->value != val) {
			prev = cur;

			if (val < cur->value)
				cur = cur->left;
			else
				cur = cur->right;

			if (cur == nullptr)
				return;
		}

		if (prev->left->value == cur->value) {
			prev->left = cur->left;
			if (cur->left == nullptr)
				prev->left = cur->right;
		}
		else {
			prev->right = cur->left;
			if (cur->left == nullptr)
				prev->right = cur->right;
		}
		delete cur;
	}

	void clear() {
		removeBranch(root);
	}

	void printFromUpToDown() {
		printFromUpToDown(root);
		std::println();
	}

	void printFromLeftToRight() {
		printFromLeftToRight(root);
		std::println();
	}

	void printFromDownToUp() {
		printFromDownToUp(root);
		std::println();
	}

	std::size_t getSize() {
		return getSize(root);
	}

	std::size_t getHeight() {
		return getHeight(root);
	}

	double getMediumHeight() {
		return  static_cast<double>(getSumLenght(root, 1)) / static_cast<double>(getSize(root));
	}
};
