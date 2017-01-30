#include "game.h"

Game::Game():Guser() , prisoners() {}

Game::Game(const Input_reader &user): Guser(user),
    prisoners(user.getNames().size()){}

Game::~Game(){}

void Game::start_game(){
    switch(recognise_mode(Guser.getMode())){
        case detailed:{
            DetailedMode temp(Guser);
            temp.run_mode();
            break;
        }
        case tournament:{
            TournamentMode temp(Guser);
            temp.run_mode();
            break;
        }
        case fast:{
            FastMode temp(Guser);
            temp.run_mode();
            break;
        }
        case nomode:{
            Guser.write_something("No mode. Cant start game. Bye!",gMove_to_new_line);
            break;
        }
    }
    return ;
}

bool Game::check_game_arguments(){
    if( nomode  == recognise_mode(Guser.getMode())){
        Guser.write_something("Enter please mode! ", gMove_to_new_line);
        Guser.write_something("Exmaple - --mode=??? --steps=??? --config== ???"
                              "--matrix=??? strategies  ", gMove_to_new_line);
        return true;
    }
    else if(!Guser.getSteps()){
        Guser.write_something("Enter pls steps!", gMove_to_new_line);
        Guser.write_something("Exmaple - --mode=??? --steps=??? --config== ???"
                              "--matrix=??? strategies  ", gMove_to_new_line);
        return true;
     }
    else if((Guser.getNames()).size() < 3 ){
        Guser.write_something("Too few prisoners. At least need 3 or more(for tournamnet mode)", gMove_to_new_line);
        Guser.write_something("Exmaple - --mode=??? --steps=??? --config=???"
                              "--matrix=??? strategies ", gMove_to_new_line);
        return true;
    }
    else if((fast == recognise_mode(Guser.getMode()) || detailed  == recognise_mode(Guser.getMode())) && (Guser.getNames()).size() > 3){
        Guser.write_something("Too many prisoners for detailed or fast mode",  gMove_to_new_line);
        Guser.write_something("Example - --mode=??? --steps=??? --config= ???"
                              "--matrix=??? strategies", gMove_to_new_line);
        return true;
    }
     else if(!(Guser.check_strategies())){
        Guser.write_something("cant recognize strategies!", gMove_to_new_line);
        return true;
    }
    return false;
}



enum Game::mode Game::recognise_mode(const std::string& _mode){
    if("detailed" == _mode){
          return detailed;
    }else if("fast" == _mode){
        return fast;
    }else if("tournament" == _mode){
        return tournament;
    }else
        return nomode;
}

