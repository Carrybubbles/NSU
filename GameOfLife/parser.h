#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <QFile>
#include <QTextStream>
#include <exception>

#include "variables.h"
#include "lifemodel.h"

class Model;
class Parser final{
public:
    Parser(Model* model);
    Parser(const Parser& another);
    ~Parser(){}
    bool is_life_format(QTextStream& in);
    bool store_params(QTextStream& in);

private:
    Model* _model = nullptr;
    std::vector<std::pair<int,int>> _alive_cells_pos;
    std::vector<std::pair<int,int>> convert_poses_to_field(QTextStream& in);

    bool store_rules(const QString& rules);
    void store_field_size();
    void store_field();
};

#endif // PARSER_H
