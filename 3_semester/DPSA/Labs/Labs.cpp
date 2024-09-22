#include "Tree.h"
#include "GraphicsTree.h"

#include <random>

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
    std::println("Tree sum: {}", tree.getSum());
    std::println("Tree height: {}", tree.getHeight());
    std::println("Tree medium height: {:.2f}", tree.getMediumHeight());
}

void lab2() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(-100, 100);

    std::vector<int> arr(100);
    for (int i = 0; i < 100; i++)
        arr[i] = dis(gen);
    PBSTree<int> tree(arr);

    std::print("From left to right: ");
    tree.printFromLeftToRight();

    std::println("Tree size: {}", tree.getSize());
    std::println("Tree sum: {}", tree.getSum());
    std::println("Tree height: {}", tree.getHeight());
    std::println("Tree medium height: {:.2f}", tree.getMediumHeight());

    GraphicsTree<int>::veiwTree({ &tree });
}

void lab3() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(-100, 100);

    std::vector<int> arr;
    for (int i = 0; i < 100; i++)
        arr.push_back(dis(gen));

    BTree<int> RSTree;
    for (int i = 0; i < 100; i++)
        RSTree.add(arr[i]);

    PBSTree<int> PBSTree(arr);

    std::print("From left to right: ");
    RSTree.printFromLeftToRight();

    std::println("\n n = 100 | Size | Sum | Height | Medium Height");

    std::println("    PBST |{:5} |{:4} |{:7} |{:14}", PBSTree.getSize(), PBSTree.getSum(), PBSTree.getHeight(), PBSTree.getMediumHeight());
    std::println("     RST |{:5} |{:4} |{:7} |{:14}", RSTree.getSize(), RSTree.getSum(), RSTree.getHeight(), RSTree.getMediumHeight());

    GraphicsTree<int>::veiwTree({ &RSTree, &PBSTree });
}

int main() {
    // lab1();
    // lab2();
    lab3();

    return 0;
}
