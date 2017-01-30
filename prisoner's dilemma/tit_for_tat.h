#ifndef TIT_FOR_TAT_H
#define TIT_FOR_TAT_H

#include "strategy.h"
// C 10 steps, then repeat another prisoner's decision
class Tat_strategy final : public Strategy{
public:
    Tat_strategy();
    ~Tat_strategy();
    bool decision(const std::vector<int>& history_1,
                  const  std::vector<int>& history_2) override;
};

#endif // TIT_FOR_TAT_H

