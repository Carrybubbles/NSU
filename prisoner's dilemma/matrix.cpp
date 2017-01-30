#include <iostream>
#include <array>
#include <fstream>

#include "matrix.h"


Matrix::Matrix(): Height(KMax_height), Width(kMax_width) {

    matrix.resize(Height, std::vector<int>(Width, 0));

    matrix[0][0] = 4;
    matrix[0][1] = 4;
    matrix[0][2] = 4;
    matrix[1][0] = 2;
    matrix[1][1] = 2;
    matrix[1][2] = 5;
    matrix[2][0] = 2;
    matrix[2][1] = 5;
    matrix[2][2] = 2;
    matrix[3][0] = 0;
    matrix[3][1] = 3;
    matrix[3][2] = 3;
    matrix[4][0] = 5;
    matrix[4][1] = 2;
    matrix[4][2] = 2;
    matrix[5][0] = 3;
    matrix[5][1] = 0;
    matrix[5][2] = 3;
    matrix[6][0] = 3;
    matrix[6][1] = 3;
    matrix[6][2] = 0;
    matrix[7][0] = 1;
    matrix[7][1] = 1;
    matrix[7][2] = 1;
}

Matrix::Matrix(const int& _Height,  const int&  _Width): Height(_Height),
                                                                                                              Width(_Width) {
    matrix.resize(_Height,  std::vector<int>(_Width, 0));
}
Matrix::~Matrix() {

}

void Matrix::show_matrix() {
    for(int i = 0 ; i < Height; i++){
        for(int j = 0 ; j < Width; j++){
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int Matrix::count_step_score(const bool& choice1, const bool& choice2,
                             const bool& choice3, const int& law_breaker){
    return matrix[!choice3 + (!choice2) * 2 + (!choice1) * 4][law_breaker];
}



Matrix::Matrix(const Matrix &other):matrix(other.matrix), Height(other.Height),
                                                                         Width(other.Width) {

}

const Matrix &Matrix::operator=(Matrix &other)
{
    if(this != &other){
        matrix = other.matrix;
        Height = other.Height;
        Width = other.Width;
    }
    return *this;
}

void Matrix::set_value(const int& value, const int& posX, const int& posY){
    matrix[posX][posY] = value;
}
