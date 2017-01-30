#ifndef OPPOSITE_STRATEGY_H
#define OPPOSITE_STRATEGY_H

#include  "strategy.h"

class Opposite_strategy final : public Strategy{
public:
    Opposite_strategy();
    ~Opposite_strategy();
    bool decision(const std::vector<int>& history_1,
                  const  std::vector<int>& history_2) override;
};

#endif // OPPOSITE_STRATEGY_H

