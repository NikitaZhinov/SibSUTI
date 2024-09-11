#include "Tree.h"

void lab1() {
    BTree<int> tree;
    tree.add(1);
    tree.add(3);
    tree.add(2);
    tree.add(5);
    tree.add(4);
    tree.add(6);

    std::print("From up to down: ");
    tree.printFromUpToDown();
    std::print("From left to right: ");
    tree.printFromLeftToRight();
    std::print("From down to up: ");
    tree.printFromDownToUp();

    std::println("Tree size: {}", tree.getSize());
    std::println("Tree height: {}", tree.getHeight());
    std::println("Tree medium height: {}", tree.getMediumHeight());
}

int main() {
    lab1();

    return 0;
}
