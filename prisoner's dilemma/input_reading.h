#ifndef INPUT_READER_H
#define INPUT_READER_H

#include <iostream>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <algorithm>

#include "matrix.h"
#include "variables.h"

class Input_reader final{
public: 
    Input_reader();
    ~Input_reader();

    void store_params_from_command_line(int argc, char** argv);
    Matrix& open_game_matrix(const std::string& _dir);

    bool check_strategies() const;
    int getSteps() const;
    void recognize_detailed_command();
    std::string getMode()const;
    std::string getConfig() const;
    std::string getDetailed_command()const;
    Matrix getMatrix() const;
    std::vector<std::string> getNames() const;
    std::vector<std::string> getStrategies() const;
    void show_score(const std::vector<int >& score);
    void write_something(const std::string& sentence, const bool& flag );
private:
    bool  is_dilemma_matrix(const std::string& _dir);
    void read_strategies_file(const std::string& _dir, std::vector<std::string>& _names);
    void read_strategies_file(const std::string& _dir, std::vector<std::string>& _names) const ;

    int Rsteps = 0;
    std::string Rmode;
    std::string Rconfig;
    std::string Rdetailed_command;
    Matrix Rgame_matrix;
    std::vector<std::string> Rnames;
    std::vector<std::string> real_strategies;
};


#endif // INPUT_READER_H
