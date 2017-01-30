#include "random_strategy.h"

Random_strategy::Random_strategy():Strategy("random") { }

Random_strategy::~Random_strategy() { }

bool Random_strategy::decision(const std::vector<int>& history_1,
                               const std::vector<int>& history_2)  {
    return  std::rand() % 2 == 0;
}

