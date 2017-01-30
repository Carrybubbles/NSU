#include "strategy.h"

Strategy::Strategy(const std::string& _name): name(_name){}
Strategy::~Strategy() {}

const std::string& Strategy::get_name() const {
    return name;
}


