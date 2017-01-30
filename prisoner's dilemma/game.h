#ifndef DILEMMA_GAME_H
#define DILEMMA_GAME_H

#include <string>
#include <vector>
#include <algorithm>

#include "input_reading.h"
#include "prisoner.h"
#include "game_modes.h"
#include "prisoner.h"
#include "input_reading.h"

class Game final {
public:
    enum mode :int {nomode = 0, tournament = 1  , fast = 2 ,  detailed = 3};

    Game();
    Game(const Input_reader& user);
    ~Game();
    void start_game();
    bool check_game_arguments();

private:
    Input_reader Guser;
    std::vector<Prisoner> prisoners;
    enum mode recognise_mode(const std::string& _mode);
};

#endif //DILEMMA_GAME_H
