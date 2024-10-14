#include "printer.h"

#include <print>

int main() {
    int error_code = 0;
    const char *db_name = "testBase1.dat";

    std::ifstream file_base(db_name, std::ios_base::binary);

    if (file_base.is_open()) {
        RecordList records = Record::getRecords(file_base);
        records.sort();

        Printer::printRecords(records);

        file_base.close();
    } else
        std::println("File {} is not found!", db_name);

    return error_code;
}
