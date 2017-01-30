#include "lifemodel.h"

Model::Model():
    field(g_default_height ,std::vector<int>(g_default_width,0)),
    next_field(g_default_height, std::vector<int>(g_default_width,0)),
    alive_rule(1,1),
    dead_rule(1,1),
    timer(new QTimer)
{
    timer->setInterval(200);
}

Model::~Model(){}

QString Model::Sget_alive_rule() const
{
   QString rule;
    std::for_each(begin(alive_rule), end(alive_rule), [&rule](const int& i){
       rule.append(QString::number(i));
    });
    return rule;
}

QString Model::Sget_dead_rule() const
{
    QString rule;
     std::for_each(begin(dead_rule), end(dead_rule), [&rule](const int& i){
        rule.append(QString::number(i));
     });
    return rule;
}

int Model::check_pos(const int& posX, const int& posY)
{
    return (posY < height && posY >= 0 && posX < width  && posX >= 0);
}

void Model::clear()
{
    std::for_each(begin(field), end(field),
                  [](std::vector<int> &i) {std::fill(i.begin(), i.end(), 0);});
}

QString Model::save_field()
{
    QString temp;
    int i = 0;
    std::for_each(std::begin(field), std::end(field),[&]
                  (const std::vector<int>& Vtemp){
        int j = 0;
        std::for_each(std::begin(Vtemp), std::end(Vtemp), [&](const int& value){
            if(ALIVE == value){
                temp.append(QString::number(j) +" " + QString::number(i) + "\n");
            }
            j++;
        });
        i++;
    });
    return temp;
}

void Model::new_Generation()
{
    for(int i = 0; i < height; i++){
       for(int j = 0; j < width; j++){
           next_field[i][j] = is_Alive(j , i);
       }
   }
    if(is_Same()){
        throw std::invalid_argument("Field doesn't change");
    }else if(!is_Dead()){
        throw std::invalid_argument("All cells are dead");
    }
    else{
        std::copy(begin(next_field), end(next_field), begin(field));
   }
}

bool Model::is_Same() const
{
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            if(next_field[i][j] != field[i][j])
                return false;
        }
    }
    return true;
}

bool Model::is_Dead() const {
    return std::for_each(begin(next_field), end(next_field),
                         [](const std::vector<int>& i ){
        return std::all_of(begin(i), end(i), [](const int& j){return j != DEAD;} );
    });
}

int Model::is_Alive(const int& posX, const int& posY)
{
    int power = count_neighbours(posX, posY);

    if(ALIVE == field[posY][posX]){
        std::vector<int>::const_iterator it = std::find(begin(alive_rule),
                                                        end(alive_rule), power);
        if(it != alive_rule.end()){
            return ALIVE;
        }else{
            return DEAD;
        }
    }else if(DEAD == field[posY][posX]){
            std::vector<int>::const_iterator it = std::find(begin(dead_rule),
                                                            end(dead_rule), power);
            if(it != dead_rule.end()){
                return ALIVE;
            }else{
                return DEAD;
        }
    }

    return ALIVE;
}

int Model::count_neighbours(int const& posX, int const& posY){
    int power = 0;

    for(int i = 0; i < g_amount_of_enviroment_pos ; i++){
        int dx = envir[i][0];
        int dy = envir[i][1];
        int _posX = ((posX+dx) + width) % width;
        int _posY = ((posY +dy) + height) % height ;
        if(check_pos(_posX, _posY)){
            power = power + field[_posY][_posX];
       }
    }
    return power;
}

void Model::set_size(const int& x, const int& y ){
    height = y;
    width = x;

    field.resize(y);
    next_field.resize(y);

    std::for_each(begin(field), end(field), [x](std::vector<int>& i){i.resize(x);});
    std::for_each(begin(next_field), end(next_field),
                  [x](std::vector<int>& i){i.resize(x);});
}
