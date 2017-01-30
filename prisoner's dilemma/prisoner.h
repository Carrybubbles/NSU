#ifndef DILEMMA_PRISONER_H
#define DILEMMA_PRISONER_H

#include "strategy.h"
#include "Factory.h"

class Prisoner final{
public:

    Prisoner();
    Prisoner(const std::string& _name);
    virtual ~Prisoner();

    void add_decision(const int& _decision);
    std::vector<int> get_history();
    const std::vector<int> get_history() const ;
    bool decide(const Prisoner& first, const Prisoner& second);
    void set_strategy(const std::string& _name);
private:
    std::unique_ptr<Strategy> strategy;
    std::vector<int> history;
};
#endif //DILEMMA_PRISONER_H
