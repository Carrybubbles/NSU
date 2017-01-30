#ifndef DILEMMA_GENTLE_STRATEGY_H
#define DILEMMA_GENTLE_STRATEGY_H

#include "strategy.h"

class Gentle_strategy final: public Strategy {
public:
    Gentle_strategy();
    ~Gentle_strategy();
    bool decision(const std::vector<int>& history_1,
                  const  std::vector<int>& history_2) override;
};
#endif //DILEMMA_GENTLE_STRATEGY_H
