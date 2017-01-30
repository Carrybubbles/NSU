#include "gentle_strategy.h"

Gentle_strategy::Gentle_strategy(): Strategy("gentle") { }
Gentle_strategy::~Gentle_strategy() { }

bool Gentle_strategy::decision(const std::vector<int>& history_1,
                               const std::vector<int>& history_2){
    return  true;
}
