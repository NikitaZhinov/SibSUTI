#include "model.h"

void getInput(ModelParams &model) {
    std::ifstream input_file(Common::input_file_name);

    input_file >> model.map_size.x >> model.map_size.y >> model.step_number;

    std::size_t R, F;
    input_file >> R >> F;
    for (std::size_t i = 0; i < R; i++) {
        AnimalParams param;
        input_file >> param.position.x >> param.position.y >> param.dir >> param.stability;
        param.speed = 1;
        model.rabbits.push_back(param);
    }
    for (std::size_t i = 0; i < F; i++) {
        AnimalParams param;
        input_file >> param.position.x >> param.position.y >> param.dir >> param.stability;
        param.speed = 2;
        model.foxes.push_back(param);
    }

    input_file.close();
}

void printMap(const std::vector<std::vector<long long>> &map) {
    std::ofstream output_file(Common::output_file_name);

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

int main() {
    ModelParams model_params;
    getInput(model_params);

    Model model(model_params);

    printMap(model.start());

	return 0;
}
