#include "rwer.h"

#include <fstream>
#include <string>

const char *RWer::input_file_name = "input.txt";
const char *RWer::output_file_name = "output.txt";

void RWer::getInput(ModelParams &model) {
    std::ifstream input_file(input_file_name);

    input_file >> model.map_size.x >> model.map_size.y >> model.step_number;

    std::size_t R, F;
    input_file >> R >> F;
    for (std::size_t i = 0; i < R; i++) {
        AnimalParams param;
        input_file >> param.position.x >> param.position.y >> param.dir >> param.stability;
        model.rabbits.push_back(param);
    }
    for (std::size_t i = 0; i < F; i++) {
        AnimalParams param;
        input_file >> param.position.x >> param.position.y >> param.dir >> param.stability;
        model.foxes.push_back(Fox(param, 0));
    }

    input_file.close();
}

void RWer::printMap(const std::vector<std::vector<long long>> &map) {
    std::ofstream output_file(output_file_name);

    for (std::size_t i = 0; i < map.size(); i++) {
        std::string line;
        for (std::size_t j = 0; j < map[i].size(); j++) {
            if (map[i][j] == 0)
                line.push_back('*');
            else
                line.append(std::format("{}", map[i][j]));
        }
        line.push_back('\n');
        output_file << line;
    }

    output_file.close();
}
