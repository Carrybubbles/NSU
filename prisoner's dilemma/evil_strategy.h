#ifndef DILEMMA_EVIL_STRATEGY_H
#define DILEMMA_EVIL_STRATEGY_H

#include "strategy.h"

class Evil_strategy final :  public   Strategy{
public:
    Evil_strategy();
    ~Evil_strategy();
    bool decision(const std::vector<int>& history_1,
                  const std::vector<int>& history_2) override;
};
#endif //DILEMMA_EVIL_STRATEGY_H
