#include "opposite_strategy.h"

Opposite_strategy::Opposite_strategy(): Strategy ("opposite"){}
Opposite_strategy::~Opposite_strategy(){}

bool Opposite_strategy::decision(const std::vector<int>& history_1,
                                 const std::vector<int>& history_2){
    if(!history_1.empty()){
        return !(history_1[history_1.size() - 1]);
    }else{
        return true;
    }
}
