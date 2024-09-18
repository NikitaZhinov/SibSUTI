#include "printer.h"

#include <print>

int main() {
    int error_code = 0;

    std::ifstream file_base("testBase1.dat", std::ios_base::binary);

    if (file_base.is_open()) {
        Record *records = Record::getRecords(file_base);

        Printer::printRecords(records);

        file_base.close();
        delete[] records;
    } else
        std::println("File testBase1.dat is not found!");

    return error_code;
}
