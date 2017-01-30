//
// Created by artem on 16.10.15.
//

#include "strategy.h"

Strategy::Strategy(const std::string& _name): name(_name){

}
Strategy::~Strategy() {

}

Strategy::Strategy(): name("unknown strategy") {
}

const std::string& Strategy::Sget() {
    return name;
}


