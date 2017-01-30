#include "prisoner.h"

#include <assert.h>

#include "Factory.h"
#include "strategy.h"



Prisoner::Prisoner(): strategy(factory.create<Strategy>("random")){}

Prisoner::Prisoner(const std::string &_name):
    strategy(factory.create<Strategy>(_name)) {}

Prisoner::~Prisoner() {}

void Prisoner::add_decision(const int& _decision) {
    history.push_back(_decision);
}

const std::vector<int> Prisoner::get_history() const {
    return history;
}

std::vector<int> Prisoner::get_history() {
    return history;
}

bool Prisoner::decide(const Prisoner &first, const Prisoner &second) {
    return strategy->decision(first.get_history(), second.get_history());
}

void Prisoner::set_strategy(const std::string &_name) {
    assert(_name != " ");
    strategy.reset(factory.create<Strategy>(_name));
}

