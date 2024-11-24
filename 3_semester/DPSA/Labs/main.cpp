#include "GraphicsTree.h"
#include "AVLTree.h"
#include "OptimalSearchTree.h"
#include "Coding.h"

#include <random>
#include <iostream>
#include <Windows.h>
#include <fstream>
#include <string>

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

    RSTree<int> rs_tree;
    for (int i = 0; i < 100; i++)
        rs_tree.add(arr[i]);

    PBSTree<int> pbs_tree(arr);

    std::print("From left to right: ");
    rs_tree.printFromLeftToRight();

    std::println("\n n = 100 | Size | Sum | Height | Medium Height");

    std::println("    PBST |{:5} |{:4} |{:7} |{:14}", pbs_tree.getSize(), pbs_tree.getSum(), pbs_tree.getHeight(), pbs_tree.getMediumHeight());
    std::println("     RST |{:5} |{:4} |{:7} |{:14}", rs_tree.getSize(), rs_tree.getSum(), rs_tree.getHeight(), rs_tree.getMediumHeight());

    rs_tree.clear();
    for (int i = 0; i < 100; i++)
        rs_tree.addRecurs(arr[i]);

    std::println("     RST |{:5} |{:4} |{:7} |{:14}", rs_tree.getSize(), rs_tree.getSum(), rs_tree.getHeight(), rs_tree.getMediumHeight());

    GraphicsTree<int>::veiwTree({ &rs_tree, &pbs_tree });
}

void lab4() {
    RSTree<int> tree;
    std::vector<int> arr(10);

    for (int &elem : arr) {
        std::cin >> elem;
        tree.add(elem);
    }

    tree.printFromLeftToRight();
    // GraphicsTree<int>::veiwTree({ &tree });

    for (int elem : arr) {
        tree.remove(elem);
        tree.printFromLeftToRight();
        // GraphicsTree<int>::veiwTree({ &tree });
    }
}

void lab5() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(-100, 100);

    AVLTree<int> avl_tree;
    PBSTree<int, AVLTreeNode<int>> pbs_tree;
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

    GraphicsTree<int, AVLTreeNode<int>>::veiwTree({ &avl_tree, &pbs_tree });
}

void lab6() {
    AVLTree<int> tree;
    std::vector<int> arr(10);

    for (int &elem : arr) {
        std::cin >> elem;
        tree.add(elem);
    }

    tree.printFromLeftToRight();
    GraphicsTree<int, AVLTreeNode<int>>::veiwTree({ &tree });

    for (int elem : arr) {
        tree.remove(elem);
        tree.printFromLeftToRight();
        GraphicsTree<int, AVLTreeNode<int>>::veiwTree({ &tree });
    }
}

// Does not apply to tasks!
void challenge() {
    // The essence of the challenge is to display the AVL tree on the screen by entering elements from the terminal with the encoding cp1251 in Cyrillic.

    SetConsoleCP(1251);

    AVLTree<char> tree;
    for (int i = 0; i < 12; i++) {
        char elem;
        std::cin >> elem;
        tree.add(elem);
    }

    GraphicsTree<char, AVLTreeNode<char>>::veiwTree({ &tree }, std::locale(".1251"));
}

void lab7() {
    BTree<int, 3> dbd_tree;
    for (int i = 0; i < 100; i++) dbd_tree.add(i);

    AVLTree<int> avl_tree;
    for (int i = 0; i < 100; i++) avl_tree.add(i);

    std::print("From left to right: ");
    dbd_tree.printFromLeftToRight();

    std::println("\n n = 100 | Size | Sum | Height | Medium Height");
    std::println("     AVL |{:5} |{:4} |{:7} |{:14.2f}", avl_tree.getSize(), avl_tree.getSum(), avl_tree.getHeight(), avl_tree.getMediumHeight());
    std::println("     DBD |{:5} |{:4} |{:7} |{:14.2f}", dbd_tree.getSize(), dbd_tree.getSum(), dbd_tree.getHeight(), dbd_tree.getMediumHeight());

    std::println("\nLevels count: {}", dbd_tree.getLevelsCount());

    GraphicsBTree<int, 3>::veiwTree({ &dbd_tree });
}

void lab8() {
    SetConsoleOutputCP(1251);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);

    std::size_t size = 7;

    std::vector<std::pair<int, uint64_t>> arr;
    for (int i = 0; i < size; i++)
        arr.push_back(std::pair<int, uint64_t>(i, dis(gen)));

    std::print("Исходный массив: ");
    for (const auto &elem : arr) std::print("{} ", elem.first);
    std::println();
    std::print("Веса массива: ");
    for (const auto &elem : arr) std::print("{} ", elem.second);
    std::println("\n");

    EOSTree<int> eost_tree(arr);
    std::print("Дерево слева на право: ");
    eost_tree.printFromLeftToRight();

    std::println("AW: ");
    eost_tree.printAW();
    std::println("AP: ");
    eost_tree.printAP();
    std::println("AR: ");
    eost_tree.printAR();

    std::println("\nAP[0,size] / AW[0,size] = {}", static_cast<double>(eost_tree.getAP()[0][size]) / static_cast<double>(eost_tree.getAW()[0][size]));
    std::println("The weighted average height tree: {}", eost_tree.weightedAverageHeightTree());

    std::println("\n n = {:3} | Size | Sum | Height | Medium Height", size);
    std::println("     EOS |{:5} |{:4} |{:7} |{:14}", eost_tree.getSize(), eost_tree.getSum(), eost_tree.getHeight(), eost_tree.getMediumHeight());

    GraphicsTree<int, OSTreeNode<int>>::veiwTree({ &eost_tree });
}

void lab9() {
    SetConsoleOutputCP(1251);

    int size = 100;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, size);

    std::vector<std::pair<int, uint64_t>> arr;
    for (int i = 0; i < size; i++)
        arr.push_back(std::pair<int, uint64_t>(i, dis(gen)));

    std::print("Исходный массив: ");
    for (const auto &elem : arr) std::print("{} ", elem.first);
    std::println();
    std::print("Веса массива: ");
    for (const auto &elem : arr) std::print("{} ", elem.second);
    std::println("\n");

    EOSTree<int> eost_tree(arr);
    OSTreeA1<int> a1_tree(arr);
    OSTreeA2<int> a2_tree(arr);
    std::print("Дерево A1 слева на право: ");
    a1_tree.printFromLeftToRight();
    std::print("Дерево A2 слева на право: ");
    a2_tree.printFromLeftToRight();

    std::println("\n n = {:3} | Size | Sum | Height | Medium Height", size);
    std::println("     EOS |{:5} |{:4} |{:7} |{:14}", eost_tree.getSize(), eost_tree.getSum(), eost_tree.getHeight(), eost_tree.getMediumHeight());
    std::println("      A1 |{:5} |{:4} |{:7} |{:14}", a1_tree.getSize(), a1_tree.getSum(), a1_tree.getHeight(), a1_tree.getMediumHeight());
    std::println("      A2 |{:5} |{:4} |{:7} |{:14}", a2_tree.getSize(), a2_tree.getSum(), a2_tree.getHeight(), a2_tree.getMediumHeight());

    GraphicsTree<int, OSTreeNode<int>>::veiwTree({ &a1_tree, &a2_tree });
}

void lab10() {
    SetConsoleOutputCP(1251);

    std::string file_name = "shennon.txt";
    std::vector<std::pair<char, float>> russian_alphabet = {
        std::pair<char, float>('а', 0.0f),
        std::pair<char, float>('б', 0.0f),
        std::pair<char, float>('в', 0.0f),
        std::pair<char, float>('г', 0.0f),
        std::pair<char, float>('д', 0.0f),
        std::pair<char, float>('е', 0.0f),
        std::pair<char, float>('ё', 0.0f),
        std::pair<char, float>('ж', 0.0f),
        std::pair<char, float>('з', 0.0f),
        std::pair<char, float>('и', 0.0f),
        std::pair<char, float>('й', 0.0f),
        std::pair<char, float>('к', 0.0f),
        std::pair<char, float>('л', 0.0f),
        std::pair<char, float>('м', 0.0f),
        std::pair<char, float>('н', 0.0f),
        std::pair<char, float>('о', 0.0f),
        std::pair<char, float>('п', 0.0f),
        std::pair<char, float>('р', 0.0f),
        std::pair<char, float>('с', 0.0f),
        std::pair<char, float>('т', 0.0f),
        std::pair<char, float>('у', 0.0f),
        std::pair<char, float>('ч', 0.0f),
        std::pair<char, float>('ц', 0.0f),
        std::pair<char, float>('ш', 0.0f),
        std::pair<char, float>('щ', 0.0f),
        std::pair<char, float>('ф', 0.0f),
        std::pair<char, float>('х', 0.0f),
        std::pair<char, float>('ь', 0.0f),
        std::pair<char, float>('ы', 0.0f),
        std::pair<char, float>('ъ', 0.0f),
        std::pair<char, float>('э', 0.0f),
        std::pair<char, float>('ю', 0.0f),
        std::pair<char, float>('я', 0.0f),
    };
    std::size_t file_size = 10240;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, russian_alphabet.size() - 1);

    // create file
    /*std::ofstream file_out(file_name);
    for (std::size_t i = 0; i < file_size; ++i) file_out << russian_alphabet[dis(gen)].first;
    file_out.close();*/

    std::ifstream file_in(file_name);
    while (!file_in.eof()) {
        char c = 0;
        file_in >> c;
        for (std::pair<char, float> &p : russian_alphabet)
            if (c == p.first) ++p.second;
    }
    for (std::pair<char, float> &p : russian_alphabet) p.second /= static_cast<float>(file_size);
    file_in.close();

    auto codes = coding::shennon(russian_alphabet);

    std::size_t max_lentgh = 0;
    for (const coding::ShennonTable &table : codes)
        if (max_lentgh < table.length_code) max_lentgh = table.length_code;

    // std::sort(codes.begin(), codes.end(), [](const coding::ShennonTable &a, const coding::ShennonTable &b) { return a.symbol < b.symbol; });

    std::println(" Char | Probability |  Code | Length Code");
    for (const coding::ShennonTable &table : codes) {
        std::print(" {:>4} | {:<11} | ", table.symbol, table.probability);
        if (table.length_code < max_lentgh)
            for (int i = 0; i < max_lentgh - table.length_code; ++i) std::print(" ");
        for (const int &i : table.code) std::print("{}", i);
        std::println(" | {}", table.length_code);
    }

    float sum = 0;
    for (const coding::ShennonTable &table : codes) {
        sum += 1.0f / std::pow(2.0f, table.length_code);
    }
    std::println("\nSUM 1/2^Li <= 1");
    std::println("{} <= 1\n", sum);

    float ml = 0, entropy = 0;
    for (const coding::ShennonTable &table : codes) {
        ml += table.probability * table.length_code;
        entropy += table.probability * -std::log2(table.probability);
    }
    std::println("Medium Length = {}", ml);
    std::println("Entropy = {}", entropy);
    std::println("Medium Length - Entropy = {}", ml - entropy);
}

int main() {
    // lab1();
    // lab2();
    // lab3();
    // lab4();
    // lab5();
    // lab6();
    // lab7();
    // lab8();
    // lab9();
    lab10();

    return 0;
}
