#include "game_modes.h"

Modes::Modes(const Input_reader& _Guser):
    input_user(_Guser){}

Modes::~Modes(){}

TournamentMode::TournamentMode(const  Input_reader& _Guser):
    Modes(_Guser){}


TournamentMode::~TournamentMode(){}

void TournamentMode::run_mode(){
    input_user.write_something("Tournament mode", gMove_to_new_line);
    std::vector<std::string> names = input_user.getNames();
    for(unsigned i = 0 ; i < names.size() - 2; i++){
        for(unsigned  j = i + 1; j < names.size() - 1;  j++){
            for(unsigned k = j + 1; k < names.size(); k++ ){

                std::vector<int> score(kMax_pris ,0);
                std::vector<std::string> subnames(kMax_pris, "");
                subnames[0] = names[i];
                subnames[1] = names[j];
                subnames[2] = names[k];
                std::vector<Prisoner> current_prisoners(kMax_pris);

                int i = 0;
                std::for_each(current_prisoners.begin(), current_prisoners.end(),
                        [&](Prisoner& prisoner){prisoner.set_strategy(subnames[i++]);});


                score = make_step(input_user.getSteps(), current_prisoners);

                input_user.write_something("Now compete these strategies " , gMove_to_new_line);
                input_user.write_something(subnames[0] , gNo_move_to_new_line);
                input_user.write_something(subnames[1] , gNo_move_to_new_line);
                input_user.write_something(subnames[2] , gMove_to_new_line);

                int min = -1;
                int min_index = -1;
                int q = 0 ;
                std::for_each(std::begin(score), std::end(score),[&](const int& current_score){
                    if(-1 == min || current_score < min){
                        min = current_score;
                        min_index = q;
                    }
                    q++;
                });
                input_user.write_something("Winner = " , gNo_move_to_new_line);
                input_user.write_something(subnames[min_index] , gMove_to_new_line);
                input_user.show_score(score);
            }
        }
    }
    return;
}

DetailedMode::DetailedMode(const Input_reader& _Guser):Modes(_Guser){}

DetailedMode::~DetailedMode(){}

void DetailedMode::run_mode(){
    input_user.write_something("Detailed mode", gMove_to_new_line);
    detailed_game();
    return;
}

FastMode::FastMode(const Input_reader& Guser):Modes(Guser){}

FastMode::~FastMode(){}

void FastMode::run_mode(){
    input_user.write_something("Fast mode", gMove_to_new_line);
    std::vector<Prisoner>prisoners(kMax_pris);
    std::vector<std::string> Rnames = input_user.getNames();

    int i = 0;
    std::for_each(prisoners.begin(), prisoners.end(), [&](Prisoner& prisoner){prisoner.set_strategy(Rnames[i++]);});

    input_user.show_score((make_step(input_user.getSteps(), prisoners)));
    return;
}

std::vector<int> Modes::make_step(const int& steps, std::vector<Prisoner>& _prisoners) {
    std::vector <int> decisions(kMax_pris,  0);
    std::vector<int> score(kMax_pris,0);
    for(int i = 0 ; i < steps; i++){
        for(int j = 0; j < kMax_pris; j++){
            decisions[j] = _prisoners[j].decide(_prisoners[(j+1) % kMax_pris], _prisoners[(j+2) % kMax_pris]);
        }

        for(int j = 0; j < kMax_pris; j++){
            _prisoners[j].add_decision(decisions[j]);
            if(decisions[j]){
               input_user.write_something("C", gNo_move_to_new_line);
            }else{
                input_user.write_something("D", gNo_move_to_new_line);
            }
        }

        input_user.write_something("", gMove_to_new_line);

        for(int j = 0; j < kMax_pris; j++){
            input_user.write_something(std::to_string(input_user.getMatrix().count_step_score(decisions[0], decisions[1], decisions[2], j)), gNo_move_to_new_line);
        }

        for(int j = 0 ; j < kMax_pris; j++){
            score[j] += input_user.getMatrix().count_step_score(decisions[0], decisions[1], decisions[2], j);
        }
        input_user.write_something("",gMove_to_new_line);
    }
    return score;
}



void DetailedMode::detailed_game(){
    int steps = 0;
    std::vector<int>  score(kMax_pris,0);
    std::vector<Prisoner> prisoners(kMax_pris);
    std::vector<std::string> Rnames = input_user.getNames();

   int i = 0;
   std::for_each(prisoners.begin(), prisoners.end(), [&](Prisoner& prisoner){prisoner.set_strategy(Rnames[i++]);});
   for(;;) {
        steps = 0;
        input_user.recognize_detailed_command();
        std::string command = input_user.getDetailed_command();
        steps = input_user.getSteps();

        if(steps && command != "quit"){
            std::vector<int > cur_score = make_step(steps, prisoners);
            //score += cur_score
            std::transform(std::begin(score), std::end(score), std::begin(cur_score), std::begin(score), std::plus<int>());
            input_user.show_score(score);
        }
        else if("quit" == command){
            break;
        }
        else {
            input_user.write_something("Sorry cant recognize words. Write as follow tick or tick<number>. If you want to exit write - quit",
                                      gMove_to_new_line);
        }
    }
    return;
}


