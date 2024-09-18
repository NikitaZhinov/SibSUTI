#include "rwer.h"

int main() {
    ModelParams model_params;
    RWer::getInput(model_params);

    Model model(model_params);

    RWer::printMap(model.start());

	return 0;
}
