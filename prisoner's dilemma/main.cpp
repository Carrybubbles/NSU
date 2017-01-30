#include <iostream>
#include "Factory.h"
#include "game.h"
#include "random_strategy.h"
#include "gentle_strategy.h"
#include "evil_strategy.h"
#include "opposite_strategy.h"
#include "tit_for_tat.h"
#include "repetition_strategy.h"
#include "matrix.h"
#include "input_reading.h"


void Reg_possible_stategies(){
    factory.add<Gentle_strategy>("gentle");
    factory.add<Evil_strategy>("evil");
    factory.add<Random_strategy>("random");
    factory.add<Opposite_strategy>("opposite");
    factory.add<Repet_strategy>("repetition");
    factory.add<Tat_strategy>("tat");
}

int main(int argc, char **argv){

    Reg_possible_stategies();
    Input_reader user;
    user.write_something("Welcome to the simulator PRIOSNER'S DILEMMA!!!", gMove_to_new_line);

    user.store_params_from_command_line(argc, argv);
    Game player(user);
    if(!player.check_game_arguments()){
        player.start_game();
    }
    return 0;
}


