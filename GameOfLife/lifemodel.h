#ifndef LIFEMODEL_H
#define LIFEMODEL_H

#include <vector>
#include <stdexcept>
#include <QTimer>
#include <memory>
#include <algorithm>
#include <functional>

#include "variables.h"
#include "parser.h"

class Model final{
    friend class Parser;
public:
    Model();
    ~Model();

    inline const int& getCell(const int& x, const int& y) const{
        return field[y][x];
    };
    inline const int& getHeight() const {
        return height;
    };
    inline const int& getWidth()  const {
        return width;
    };

    inline const std::vector<std::vector<int>>& getField() const{
        return field;
    };
    inline const std::vector<std::vector<int>>& getNField() const{
        return next_field;
    };
    inline QTimer* getTimer() const {
        return timer.get();
    };
    inline std::vector<int>& get_Valive() {return alive_rule;}
    inline std::vector<int>& get_Vdead()  {return dead_rule;}
    QString Sget_alive_rule() const ;
    QString Sget_dead_rule() const ;

    inline void setCell(const int& x,const  int& y) {field[y][x] = ALIVE;}
    inline void deleteCell(const int& x,const  int& y){field[y][x] = DEAD;}
    inline bool isEmpty(const int& x, const int& y)const{return field[y][x] == DEAD;}

    void new_Generation();
    void set_size(const int& x, const int& y);
    void clear();
    int check_pos(const int& posX, const int& posY);
    QString save_field();

private:

    std::vector<std::vector<int>> field;
    std::vector<std::vector<int>> next_field;   
    int height = 15;
    int width = 15;
    std::vector<int> alive_rule;
    std::vector<int> dead_rule;
    std::unique_ptr<QTimer> timer = nullptr;
    int is_Alive(const int& posX, const int& posY) ;
    int count_neighbours(int const& posX, int const& posY);
    bool is_Same() const ;
    bool is_Dead() const ;
};

#endif // LIFEMODEL_H
