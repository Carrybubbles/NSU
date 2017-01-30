#ifndef DILEMMA_MATRIX_H
#define DILEMMA_MATRIX_H

#include <vector>
#include "variables.h"

class Matrix final{
public:
    Matrix();
    Matrix(const int& _Height, const int&  _Width);
    Matrix(const Matrix& other);
    const Matrix& operator=(Matrix& other);
    virtual~Matrix();
  
    void set_value(const int& value, const int& posX, const int& poxY);
    int count_step_score(const bool& choice1,const bool& choice2, const bool& choice3, const int& law_breaker);

private:
    void show_matrix();
    std::vector<std::vector<int>> matrix;
    int Height;
    int Width;
};
#endif //DILEMMA_MATRIX_H
