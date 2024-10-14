#include "Tree.h"
#include "GraphicsTree.h"

#include <random>
#include <iostream>

void lab1() {
    RSTree<int> tree;
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

    RSTree<int> RSTree;
    for (int i = 0; i < 100; i++)
        RSTree.add(arr[i]);

    PBSTree<int> PBSTree(arr);

    std::print("From left to right: ");
    RSTree.printFromLeftToRight();

    std::println("\n n = 100 | Size | Sum | Height | Medium Height");

    std::println("    PBST |{:5} |{:4} |{:7} |{:14}", PBSTree.getSize(), PBSTree.getSum(), PBSTree.getHeight(), PBSTree.getMediumHeight());
    std::println("     RST |{:5} |{:4} |{:7} |{:14}", RSTree.getSize(), RSTree.getSum(), RSTree.getHeight(), RSTree.getMediumHeight());

    RSTree.clear();
    for (int i = 0; i < 100; i++)
        RSTree.addRecurs(arr[i]);

    std::println("     RST |{:5} |{:4} |{:7} |{:14}", RSTree.getSize(), RSTree.getSum(), RSTree.getHeight(), RSTree.getMediumHeight());

    GraphicsTree<int>::veiwTree({ &RSTree, &PBSTree });
}

void lab4() {
    RSTree<int> RSTree;
    std::vector<int> arr(10);

    for (int &elem : arr) {
        std::cin >> elem;
        RSTree.add(elem);
    }

    RSTree.printFromLeftToRight();
    //GraphicsTree<int>::veiwTree({ &RSTree });

    for (int elem : arr) {
        RSTree.remove(elem);
        RSTree.printFromLeftToRight();
        // GraphicsTree<int>::veiwTree({ &RSTree });
    }
}

void lab5() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(-100, 100);

    AVLTree<int> avl_tree;
    PBSTree<int> pbs_tree;
    std::vector<int> arr;

    for (int i = 0; i < 100; i++)
        arr.push_back(dis(gen));

    for (int &elem : arr) {
        avl_tree.add(elem);
        pbs_tree.add(elem);
    }

    std::print("From left to right: ");
    avl_tree.printFromLeftToRight();

    std::println("\n n = 100 | Size | Sum | Height | Medium Height");

    std::println("     PBS |{:5} |{:4} |{:7} |{:14}", pbs_tree.getSize(), pbs_tree.getSum(), pbs_tree.getHeight(), pbs_tree.getMediumHeight());
    std::println("     AVL |{:5} |{:4} |{:7} |{:14}", avl_tree.getSize(), avl_tree.getSum(), avl_tree.getHeight(), avl_tree.getMediumHeight());

    GraphicsTree<int>::veiwTree({ &avl_tree, &pbs_tree });
}

int main() {
    // lab1();
    // lab2();
    // lab3();
    // lab4();
    lab5();

    return 0;
}
