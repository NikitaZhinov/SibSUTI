#include "GraphicsTree.h"
#include "AVLTree.h"
#include "OptimalSearchTree.h"
#include "Coding.h"
#include "String.h"

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

void lab11(std::vector<coding::Table> &alphabet, std::vector<coding::Table> &str) {
    coding::fano_A2(alphabet);

    std::size_t max_lentgh = 0;
    for (const coding::Table &table : alphabet)
        if (max_lentgh < table.code.size()) max_lentgh = table.code.size();

    std::println(" Char | Probability |   Code | Length Code");
    for (const coding::Table &table : alphabet) {
        std::print(" {:>4} | {:<11f} | ", table.symbol, table.probability);
        if (table.code.size() < max_lentgh)
            for (int i = 0; i < max_lentgh - table.code.size(); ++i) std::print(" ");
        for (const int &i : table.code) std::print("{}", i);
        std::println(" | {}", table.code.size());
    }

    double sum = 0;
    for (const coding::Table &table : alphabet) {
        sum += 1.0f / std::pow(2.0f, table.code.size());
    }
    double ml = 0, entropy = 0;
    for (const coding::Table &table : alphabet) {
        ml += table.probability * table.code.size();
        entropy += table.probability * -std::log2(table.probability);
    }

    std::println("\n Неравенство Крафта |                            Энтропия |    Средняя длинна |         Избыточность");
    std::println("    SUM 1/2^Li <= 1 | H(P1, ..., Pn) = SUM Pi * -log2(Pi) | Lср = SUM Pi * Li | Lср - H(P1, ..., Pn)");
    std::println("{:14f} <= 1 | {:35f} | {:17f} | {:20f}", sum, entropy, ml, ml - entropy);

    std::print("\nТекст: ");
    int i = 0;
    for (coding::Table &s : str) {
        for (coding::Table &t : alphabet) {
            if (s.symbol == t.symbol) {
                s.code = t.code;
                break;
            }
        }
        std::print("{}", s.symbol);
    }
    std::print("\nКод: ");
    std::size_t code_size = 0;
    for (const coding::Table &s : str) {
        for (auto i : s.code) {
            std::print("{}", i);
            ++code_size;
        }
    }
    std::println("\nРазмер исходной строки: 800\nДлинна кода: {}\nКоэффициент сжатия данных: {}", code_size, static_cast<double>(code_size) / 800.0f);
}

void lab10_13() {
    SetConsoleOutputCP(1251);

    std::string file_name = "chars.txt";
    int file_size = 10240;

    std::vector<coding::Table> alphabet = {
        coding::Table({ 'a' }),
        coding::Table({ 'б' }),
        coding::Table({ 'в' }),
        coding::Table({ 'г' }),
        coding::Table({ 'д' }),
        coding::Table({ 'е' }),
        coding::Table({ 'ё' }),
        coding::Table({ 'ж' }),
        coding::Table({ 'з' }),
        coding::Table({ 'и' }),
        coding::Table({ 'й' }),
        coding::Table({ 'к' }),
        coding::Table({ 'л' }),
        coding::Table({ 'м' }),
        coding::Table({ 'н' }),
        coding::Table({ 'о' }),
        coding::Table({ 'п' }),
        coding::Table({ 'р' }),
        coding::Table({ 'с' }),
        coding::Table({ 'т' }),
        coding::Table({ 'у' }),
        coding::Table({ 'ф' }),
        coding::Table({ 'х' }),
        coding::Table({ 'ц' }),
        coding::Table({ 'ч' }),
        coding::Table({ 'ш' }),
        coding::Table({ 'щ' }),
        coding::Table({ 'ъ' }),
        coding::Table({ 'ы' }),
        coding::Table({ 'ь' }),
        coding::Table({ 'э' }),
        coding::Table({ 'ю' }),
        coding::Table({ 'я' })
    };

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, alphabet.size() - 1);

    std::ifstream file(file_name);
    if (!file.is_open()) {
        std::ofstream file_out(file_name);
        for (std::size_t i = 0; i < file_size; ++i) file_out << alphabet.at(dis(gen)).symbol;
        file_out.close();
        file.open(file_name);
    }

    while (!file.eof()) {
        char c = 0;
        file >> c;
        for (coding::Table &symbol : alphabet)
            if (c == symbol.symbol) ++symbol.probability;
    }
    for (coding::Table &symbol : alphabet) symbol.probability /= static_cast<double>(file_size);
    file.close();

    // coding::shennon(alphabet); // lab 10
    // coding::fano(alphabet); // lab 11
    // coding::huffman(alphabet); // lab 12
    // coding::gilbert_mur(alphabet); // lab 13

    std::size_t max_lentgh = 0;
    for (const coding::Table &table : alphabet)
        if (max_lentgh < table.code.size()) max_lentgh = table.code.size();

    std::println(" Char | Probability |   Code | Length Code");
    for (const coding::Table &table : alphabet) {
        std::print(" {:>4} | {:<11f} | ", table.symbol, table.probability);
        if (table.code.size() < max_lentgh)
            for (int i = 0; i < max_lentgh - table.code.size(); ++i) std::print(" ");
        for (const int &i : table.code) std::print("{}", i);
        std::println(" | {}", table.code.size());
    }

    double sum = 0;
    for (const coding::Table &table : alphabet) {
        sum += 1.0f / std::pow(2.0f, table.code.size());
    }
    double ml = 0, entropy = 0;
    for (const coding::Table &table : alphabet) {
        ml += table.probability * table.code.size();
        entropy += table.probability * -std::log2(table.probability);
    }

    std::println("\n Неравенство Крафта |                            Энтропия |    Средняя длинна |         Избыточность");
    std::println("    SUM 1/2^Li <= 1 | H(P1, ..., Pn) = SUM Pi * -log2(Pi) | Lср = SUM Pi * Li | Lср - H(P1, ..., Pn)");
    std::println("{:14f} <= 1 | {:35f} | {:17f} | {:20f}", sum, entropy, ml, ml - entropy);

    std::print("\nТекст: ");
    std::vector<coding::Table> str(100);
    for (coding::Table &s : str) {
        s = alphabet.at(dis(gen));
        std::print("{}", s.symbol);
    }
    std::print("\nКод: ");
    std::size_t code_size = 0;
    for (coding::Table &s : str) {
        for (auto i : s.code) {
            std::print("{}", i);
            ++code_size;
        }
    }
    std::println("\nРазмер исходной строки: 800\nДлинна кода: {}\nКоэффициент сжатия данных: {}\n", code_size, static_cast<double>(code_size) / 800.0f);

    // lab11(alphabet, str);
}

void lab14() {
    SetConsoleOutputCP(1251);

    std::string str = "Декабрь - это волшебный месяц, когда границы между реальностью и сказкой стираются, и снег, словно пушистая перина, накрывает землю. С началом зимы начинается время праздников, тепла и уюта, которое хочется запечатлеть не только в сердце, но и в каждом взгляде на экран своего телефона или компьютера.";
    std::string word = "снег";

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, str.size() - 1);

    int compares = 0;
    auto indexes = str::strstr(str, word, compares);

    std::println("Text: {}", str);
    std::println("Word: {}", word);
    std::print("\n    Simple Indexes: ");
    for (int index : indexes) std::print("{} ", index);
    std::println("\nCompares: {}\n", compares);

    compares = 0;
    indexes = str::rabin_losos(str, word, compares);
    std::print("Rabin-Karp Indexes: ");
    for (int index : indexes) std::print("{} ", index);
    std::println("\nCompares: {}", compares);
}

void dz() {
    SetConsoleOutputCP(1251);

    std::vector<coding::Table> alphabet = {
        coding::Table({ 'ж' }),
        coding::Table({ 'и' }),
        coding::Table({ 'н' }),
        coding::Table({ 'о' }),
        coding::Table({ 'в' }),
        coding::Table({ 'к' }),
        coding::Table({ 'т' }),
        coding::Table({ 'а' }),
        coding::Table({ 'д' }),
        coding::Table({ 'р' })
    };

    alphabet.at(0).probability = 0.07;
    alphabet.at(1).probability = 0.22;
    alphabet.at(2).probability = 0.12;
    alphabet.at(3).probability = 0.07;
    alphabet.at(4).probability = 0.12;
    alphabet.at(5).probability = 0.07;
    alphabet.at(6).probability = 0.07;
    alphabet.at(7).probability = 0.12;
    alphabet.at(8).probability = 0.07;
    alphabet.at(9).probability = 0.07;

    coding::gilbert_mur(alphabet);

    std::size_t max_lentgh = 0;
    for (const coding::Table &table : alphabet)
        if (max_lentgh < table.code.size()) max_lentgh = table.code.size();

    std::println(" Char | Probability |   Code | Length Code");
    for (const coding::Table &table : alphabet) {
        std::print(" {:>4} | {:<11} | ", table.symbol, table.probability);
        if (table.code.size() < max_lentgh)
            for (int i = 0; i < max_lentgh - table.code.size(); ++i) std::print(" ");
        for (const int &i : table.code) std::print("{}", i);
        std::println(" | {}", table.code.size());
    }

    double sum = 0;
    for (const coding::Table &table : alphabet) {
        sum += 1.0f / std::pow(2.0f, table.code.size());
    }
    double ml = 0, entropy = 0;
    for (const coding::Table &table : alphabet) {
        ml += table.probability * table.code.size();
        entropy += table.probability * -std::log2(table.probability);
    }

    std::println("\n Неравенство Крафта |                            Энтропия |    Средняя длинна |         Избыточность");
    std::println("    SUM 1/2^Li <= 1 | H(P1, ..., Pn) = SUM Pi * -log2(Pi) | Lср = SUM Pi * Li | Lср - H(P1, ..., Pn)");
    std::println("{:14f} <= 1 | {:35f} | {:17} | {:20}", sum, entropy, ml, ml - entropy);
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
    // lab10_13();
    // lab14();

    std::vector<std::pair<char, uint64_t>> arr = {
        std::pair<char, uint64_t>('р', 1),
        std::pair<char, uint64_t>('ы', 1),
        std::pair<char, uint64_t>('б', 1),
        std::pair<char, uint64_t>('к', 2)
    };

    EOSTree<char> tree(arr);

    return 0;
}
