#include "repetition_strategy.h"

Repet_strategy::Repet_strategy():Strategy("repetition"){}
Repet_strategy::~Repet_strategy(){}
bool Repet_strategy::decision(const std::vector<int>& history_1,
                              const std::vector<int>& history_2){
    if(!history_1.empty()){
        return history_1[history_1.size() - 1];
    }
    else{
        return true;
    }
}
