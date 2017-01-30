#ifndef DILEMMA_RANDOM_STRATEGY_H
#define DILEMMA_RANDOM_STRATEGY_H

#include "strategy.h"

class Random_strategy final : public Strategy{
public:
    Random_strategy();
    ~Random_strategy();
    bool decision(const std::vector<int>& history_1,
                  const std::vector<int>& history_2) override ;
};
#endif //DILEMMA_RANDOM_STRATEGY_H
