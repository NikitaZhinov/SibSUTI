#include <cmath>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct Record {
    char FIO[200];
    int number_of_seats;
    int weight;
};

void createNewFile() {
    system("clear");
    std::string filename;
    int number_of_record;
    std::cout << "Введите название файла: ";
    std::cin >> filename;
    std::cout << "Введите количество записей: ";
    std::cin >> number_of_record;

    std::ofstream file(filename, std::ios_base::binary);
    if (file.is_open()) {
        for (int i = 1; i <= std::abs(number_of_record); i++) {
            Record record;
            std::cout << i << ": ";
            std::cin >> record.FIO >> record.number_of_seats >> record.weight;
            file.write(record.FIO, sizeof(record.FIO));
            file.write((char *)&record.number_of_seats, sizeof(record.number_of_seats));
            file.write((char *)&record.weight, sizeof(record.weight));
        }
        file.close();
    } else {
        std::cout << "Ошибка создания файла(" << std::endl;
        std::cin >> filename;
    }
}

void viewFile() {
    system("clear");
    std::string filename;
    std::cout << "Введите название файла: ";
    std::cin >> filename;

    std::ifstream file(filename, std::ios_base::binary);
    if (file.is_open()) {
        // char c = file.get();
        // while (!file.eof()) {
        //     std::cout << c;
        //     c = file.get();
        // }
        std::filesystem::path p = filename.c_str();
        size_t i = 0;
        while (i < std::filesystem::file_size(p)) {
            Record record;
            file.read(record.FIO, sizeof(record.FIO));
            file.read((char *)&record.number_of_seats, sizeof(record.number_of_seats));
            file.read((char *)&record.weight, sizeof(record.weight));
            std::cout << record.FIO << " " << record.number_of_seats << " " << record.weight << std::endl;
            i += sizeof(record.FIO) + sizeof(record.number_of_seats) + sizeof(record.weight);
        }
        file.close();
    } else
        std::cout << "Ошибка открытия файла(" << std::endl;
    std::cin >> filename;
}

void addNewRecord() {
    system("clear");
    std::string filename;
    std::cout << "Введите название файла: ";
    std::cin >> filename;

    std::ofstream file(filename, std::ios_base::binary | std::ios_base::app);
    if (file.is_open()) {
        // std::string text;
        // char c = file_.get();
        // while (!file_.eof()) {
        //     text.push_back(c);
        //     c = file_.get();
        // }
        // std::ofstream file(filename, std::ios_base::binary);
        Record record;
        // file << text;
        std::cin >> record.FIO >> record.number_of_seats >> record.weight;
        // file << record.FIO << " " << record.number_of_seats << " " << record.weight << std::endl;
        file.write(record.FIO, sizeof(record.FIO));
        file.write((char *)&record.number_of_seats, sizeof(record.number_of_seats));
        file.write((char *)&record.weight, sizeof(record.weight));
        file.close();
    } else {
        std::cout << "Ошибка открытия файла(" << std::endl;
        std::cin >> filename;
    }
}

void removeLightPeople() {
    system("clear");
    std::string filename;
    std::cout << "Введите название файла: ";
    std::cin >> filename;

    std::ifstream file(filename, std::ios_base::binary);
    if (file.is_open()) {
        std::vector<Record> lines;
        std::filesystem::path p = filename.c_str();
        size_t i = 0;
        while (i < std::filesystem::file_size(p)) {
            Record record;
            file.read(record.FIO, sizeof(record.FIO));
            file.read((char *)&record.number_of_seats, sizeof(record.number_of_seats));
            file.read((char *)&record.weight, sizeof(record.weight));
            if (record.weight >= 10)
                lines.push_back(record);
            i += sizeof(record.FIO) + sizeof(record.number_of_seats) + sizeof(record.weight);
        }
        file.close();
        std::ofstream file_(filename, std::ios_base::binary);
        for (auto record : lines) {
            file_.write(record.FIO, sizeof(record.FIO));
            file_.write((char *)&record.number_of_seats, sizeof(record.number_of_seats));
            file_.write((char *)&record.weight, sizeof(record.weight));
        }
        file_.close();
    } else {
        std::cout << "Ошибка открытия файла(" << std::endl;
        std::cin >> filename;
    }
}

void changeWeight() {
    system("clear");
    std::string filename;
    std::cout << "Введите название файла: ";
    std::cin >> filename;
    std::string FIO;
    std::cout << "Введите ФИО пассажира (без пробелов): ";
    std::cin >> FIO;
    int new_weight;
    std::cout << "Введите новый вес: ";
    std::cin >> new_weight;

    std::ifstream file(filename, std::ios_base::binary);
    if (file.is_open()) {
        std::vector<Record> lines;
        std::filesystem::path p = filename.c_str();
        size_t i = 0;
        while (i < std::filesystem::file_size(p)) {
            Record record;
            file.read(record.FIO, sizeof(record.FIO));
            file.read((char *)&record.number_of_seats, sizeof(record.number_of_seats));
            file.read((char *)&record.weight, sizeof(record.weight));
            if (record.FIO == FIO)
                record.weight = new_weight;
            lines.push_back(record);
            i += sizeof(record.FIO) + sizeof(record.number_of_seats) + sizeof(record.weight);
        }
        file.close();
        std::ofstream file_(filename, std::ios_base::binary);
        for (auto record : lines) {
            file_.write(record.FIO, sizeof(record.FIO));
            file_.write((char *)&record.number_of_seats, sizeof(record.number_of_seats));
            file_.write((char *)&record.weight, sizeof(record.weight));
        }
        file_.close();
    } else {
        std::cout << "Ошибка открытия файла(" << std::endl;
        std::cin >> filename;
    }
}

int main() {
    int mode;

    do {
        system("clear");
        std::cout << "1 - Создать новый файл" << std::endl;
        std::cout << "2 - Просмотреть файл" << std::endl;
        std::cout << "3 - Добавить запись" << std::endl;
        std::cout << "4 - Удалить лёгких людей" << std::endl;
        std::cout << "5 - Изменить вес пасажира" << std::endl;
        std::cout << "0 - Выйти" << std::endl;
        std::cin >> mode;

        switch (mode) {
            case 1:
                createNewFile();
                break;

            case 2:
                viewFile();
                break;

            case 3:
                addNewRecord();
                break;

            case 4:
                removeLightPeople();
                break;

            case 5:
                changeWeight();
                break;

            case 0:
                break;

            default:
                system("clear");
                std::cout << "ШО?!" << std::endl
                          << "Попробовать ещё раз" << std::endl;
                std::cin >> mode;
                break;
        }
    } while (mode != 0);

    return 0;
}