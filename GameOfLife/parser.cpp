#include "parser.h"

Parser::Parser(Model* model):_model(model),
    _alive_cells_pos()
 {}

Parser::Parser(const Parser& another): _model(another._model), _alive_cells_pos(another._alive_cells_pos)
{}

bool Parser::is_life_format(QTextStream& in)
{
    QString format  = in.readLine();
    return format == "#Life 1.06";
}

bool Parser::store_params(QTextStream& in)
{
    //find rules and store it
    while(!in.atEnd()){
        QString format = in.readLine();
        if('#' == format[0]){
            QStringList substring = format.split(' ');
            if("#R" == substring[0]){
                if(!store_rules(substring[1]))
                    throw std::invalid_argument("Cant recognize rule!");
                else
                    break;
            }
        }
    }

    _alive_cells_pos = convert_poses_to_field(in);
    store_field_size();
    store_field();
    return true;
}
bool Parser::store_rules(const QString &rules)
{
    int alive_pos = 0;
    std::vector<int> alive_rule;
    std::vector<int> dead_rule;
    for(int i = 0 ; rules[i] != '/'; i++){
        if(!rules[i].digitValue()){
            return false;
        }
        dead_rule.push_back(rules[i].digitValue());
        alive_pos = i;
    }
    for(int i = alive_pos + 2; i < rules.size(); i++){
        if(!rules[i].digitValue()){
            return false;
        }
        alive_rule.push_back(rules[i].digitValue());
    }
    _model->alive_rule = alive_rule;
    _model->dead_rule = dead_rule;
    return true;
}

void Parser::store_field_size()
{
     auto maxX = std::max_element(begin(_alive_cells_pos),
                               end(_alive_cells_pos), [](std::pair<int,int>& p,
                                std::pair<int,int>&g){
        return p.first < g.first;});

     if(maxX->first < g_default_width){
         _model->width = g_default_width;
     }else{
         _model->width = maxX->first + 1;
     }

     auto maxY = std::max_element(begin(_alive_cells_pos),
                               end(_alive_cells_pos), [](std::pair<int,int>& p,
                                std::pair<int,int>&g){
        return p.second < g.second;});

     if(maxY->second < g_default_height){
         _model->height = g_default_height;
     }else{
         _model->height = maxY->second + 1;
    }
}

void Parser::store_field()
{
   std::vector<std::vector<int>> new_field(_model->getHeight(),
          std::vector<int>(_model->getWidth()));
   std::vector<std::vector<int>> new_next_field(_model->getHeight(),
          std::vector<int>(_model->getWidth()));

   _model->field = new_field;
   _model->next_field = new_next_field;
   std::for_each(_alive_cells_pos.begin(), _alive_cells_pos.end(),
                  [this](std::pair<int,int>& i){_model->setCell(i.first, i.second);});
}

std::vector<std::pair<int, int> > Parser::convert_poses_to_field(QTextStream& in)
{
       std::vector<std::pair<int,int>> temp;
       while(!in.atEnd()){
           bool ok;

           QString posX;
           in >> posX;
           if(posX == "")
               break;
           posX.toInt(&ok);
           if(!ok){
                throw std::invalid_argument("incorrect X");
           }

           QString posY;
           in >> posY;
           if(posY == "")
               break;
           posY.toInt(&ok);
           if(!ok){
                throw std::invalid_argument("incorrect Y");
           }
           temp.push_back(std::make_pair(posX.toInt(&ok), posY.toInt(&ok)));
       }
       return temp;
}


