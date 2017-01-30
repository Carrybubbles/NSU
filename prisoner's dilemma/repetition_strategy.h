#ifndef REPETITION_STRATEGY_H
#define REPETITION_STRATEGY_H

#include "strategy.h"

class Repet_strategy final : public Strategy{
public:
    Repet_strategy();
    ~Repet_strategy();
    bool decision(const std::vector<int>& history_1,
                  const  std::vector<int>& history_2) override;
};

#endif // REPETITION_STRATEGY_H

