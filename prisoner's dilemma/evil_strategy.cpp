#include "evil_strategy.h"

Evil_strategy::Evil_strategy(): Strategy("evil") {}
Evil_strategy::~Evil_strategy() { }

bool Evil_strategy::decision(const std::vector<int>&  history_1,
                             const  std::vector<int>& history_2) {
    return false;
}
