#include "input_reading.h"



Input_reader::Input_reader():Rsteps(0), Rmode(), Rconfig(), Rdetailed_command(),
                                                            Rgame_matrix(), Rnames(), real_strategies(){

}
Input_reader::~Input_reader(){

}

void Input_reader::read_strategies_file(const std::string &_dir,
                                   std::vector<std::string>& _names){
    std::ifstream file;
    file.open(_dir);
    if(!file){
       std::cout << "Cant open file with strategies!" << std::endl;
       return;
    }else{
        std::string name;
        while(file >> name){
            _names.push_back(name);
        }
        file.close();
    }
}

void Input_reader::read_strategies_file(const std::string &_dir,
                                   std::vector<std::string> &_names)const{
    std::ifstream file;
    file.open(_dir);
    if(!file){
       std::cout << "Cant open file with strategies!" << std::endl;
       return;
    }else{
        std::string name;
        while(file >> name){
            _names.push_back(name);
        }
    file.close();
   }
}


bool Input_reader::check_strategies() const{
   std::vector<std::string> Fnames;
   std::string dir("strategies.txt");
   read_strategies_file(dir , Fnames);

   bool flag = false;
   for(unsigned i = 0 ; i < Rnames.size(); i++){
        if(std::find(Fnames.begin(), Fnames.end(), Rnames[i]) == Fnames.end())
            flag = true;
   }
  return flag == false;
}


int Input_reader::getSteps() const
{
    return Rsteps;
}

void Input_reader::recognize_detailed_command()
{
    std::string temp;
    std::cin >> temp;
    int  steps = 0;
    std::string command;
    if(temp == "quit"){
        command = temp;
    }
    else if(temp.find("tick<") != std::string::npos){
        unsigned count = 0;
        for(unsigned i = 5 ; isdigit(temp[i]) ; i++){
            count++;
            steps = steps*10 + temp[i] - '0';
        }
        if(count != temp.size() - 6)
            steps = 0;
    }
    else{
       steps = 0;
    }
    Rsteps = steps;
    Rdetailed_command = command;
}

std::string Input_reader::getMode() const {
    return Rmode;
}

std::string Input_reader::getConfig() const {
    return Rconfig;
}

std::string Input_reader::getDetailed_command() const
{
    return Rdetailed_command;
}

Matrix Input_reader::getMatrix() const {
    return Rgame_matrix;
}

std::vector<std::string> Input_reader::getNames() const
{
    return Rnames;
}

std::vector<std::string> Input_reader::getStrategies() const
{
    return real_strategies;
}


bool  Input_reader::is_dilemma_matrix(const std::string& _dir){
    std::ifstream file;
    file.open(_dir);

    if(!file){
        std::cout << "Cant open file with matrix! " << std::endl;
        return false;
    }else{
        std::string check;
        file >> check;
        file.close();
        return check == "DILEMMA";
    }
}

Matrix& Input_reader::open_game_matrix(const std::string& _dir){
    std::ifstream file;

    if (is_dilemma_matrix(_dir)){
        file.open(_dir);
        std::string name;
        file >> name;
        for(int i = 0 ; i < KMax_height; i++){
            for(int j = 0 ; j < kMax_width; j++){
                int value = 0;
                file >> value;
                Rgame_matrix.set_value(value, i , j);
            }
        }
        file.close();
        return Rgame_matrix;
    }else{
        throw  std::invalid_argument("Cant open or read game_matrix from file");
    }
}


void  Input_reader::store_params_from_command_line(int argc , char **argv) {
    std::vector<std::string> settings;
    settings.assign(argv  + 1, argc + argv);
    std::string sub_buf;

    for(int unsigned  i = 0 ; i < settings.size(); i++){
        std::string buffer = settings[i];

        if(buffer.find("--mode=") != std::string::npos){
            sub_buf = settings[i].substr(7 , settings[i].size() - 7);
            Rmode = sub_buf;
        }

        else if(buffer.find("--steps=") != std::string::npos){
            for(int i = 8;  isdigit(buffer[i]); i++){
                Rsteps = Rsteps*10 +  buffer[i] - '0';
            }
        }

        else if(buffer.find("--configs=") != std::string::npos){
            sub_buf = settings[i].substr(10 ,  settings[i].size() - 10);
            Rconfig = sub_buf;
        }

        else if(buffer.find("--matrix=") != std::string::npos ){
            sub_buf = settings[i].substr(9 ,  settings[i].size() - 9);
            try{
                Rgame_matrix = open_game_matrix(sub_buf);
            }
            catch(std::exception& er){
                std::cout << er.what() << std::endl;
                std::cout << "We enter default game_matrix" << std::endl;
            }
        }
        else{
            Rnames.push_back(settings[i]);
        }
    }
}

void Input_reader::show_score(const std::vector<int>& score) {
    std::cout << "Score_table" << std::endl;
    std::cout << "First prisoner = " << score[0] << std::endl;
    std::cout << "Second prisoner = " << score[1] << std::endl;
    std::cout << "Third prisoner = " << score[2] << std::endl;
}

void Input_reader::write_something(const std::string &sentence, const bool& flag)
{
    if(flag){
        std::cout << sentence << " ";
    }else{
        std::cout << sentence << std::endl;
    }
}
