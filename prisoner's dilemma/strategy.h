#ifndef DILEMMA_STRATEGY_H
#define DILEMMA_STRATEGY_H

#include <vector>
#include <string>

class Strategy{
public:
    Strategy(const std::string& _name = "random");
    virtual ~Strategy();

    const std::string& get_name() const;

     virtual bool decision(const std::vector<int>& history_1,
                          const std::vector<int>& history_2) = 0;

private:
    std::string name;
};

#endif //DILEMMA_STRATEGY_H
