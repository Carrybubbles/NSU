#include "tit_for_tat.h"

Tat_strategy::Tat_strategy(): Strategy("tat"){}
Tat_strategy::~Tat_strategy(){}

bool Tat_strategy::decision(const std::vector<int>& history_1,
                            const std::vector<int>& history_2){
    if(history_1.size() < 10){
        return true;
    }else{
        return history_1[history_2.size() - 1];
    }
}
