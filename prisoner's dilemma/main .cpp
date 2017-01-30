//
// Created by artem on 16.10.15.
//

#include <iostream>
#include "Factory.h"
#include "random_strategy.h"
#include "gentle_strategy.h"
#include "god.h"
Factory factory;

int main(){
    std::vector<std::string> qwe;
    qwe.push_back("random");
    qwe.push_back("rofl");
    qwe.push_back("123");
    //int* lol = nullptr;
    //std::cout << *lol;
    factory.add<Random_strategy>("random");
    factory.add<Random_strategy>("rofl");
    factory.add<Random_strategy>("123");
    God h(qwe);
    h.game();
    return 0;
}