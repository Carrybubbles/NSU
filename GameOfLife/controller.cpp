#include "controller.h"


Controller::Controller(Model* model, View* view):
    _model(model), _view(view)
{
    _view->connect(_view->get_Bstart() ,SIGNAL(clicked()), this , SLOT(start_game()));
    _view->connect(_view->get_Bstop(), SIGNAL(clicked()), this,  SLOT(stop_game()));
    _view->connect(_view->get_Bclear(),SIGNAL(clicked()),  this, SLOT(clear_field()));
    _view->connect(_model->getTimer(), SIGNAL(timeout()), this, SLOT(generate()) );
    _view->connect(_view->get_Bwidth(), SIGNAL(valueChanged(int)), this, SLOT(changeX(int)));
    _view->connect(_view->get_Bheight(), SIGNAL(valueChanged(int)), this, SLOT(changeY(int)));
    _view->connect(_view->get_Bsave(), SIGNAL(clicked()), this, SLOT(save_game()));
    _view->connect(_view->get_Bload(), SIGNAL(clicked()), this, SLOT(load_game()));
    _view->connect(_view->get_Btime(), SIGNAL(valueChanged(double)), this, SLOT(change_time(double)));
    _view->connect(_view->get_Bmin_alive(), SIGNAL(valueChanged(int)), this,SLOT(change_alive_rule()));
    _view->connect(_view->get_Bmax_alive(), SIGNAL(valueChanged(int)), this,SLOT(change_alive_rule()));
    _view->connect(_view->get_Bmin_dead() , SIGNAL(valueChanged(int)), this,SLOT(change_dead_rule()));
    _view->connect(_view->get_Bmax_dead() , SIGNAL(valueChanged(int)), this,SLOT(change_dead_rule()));
}

Controller::~Controller() {}


void Controller::start_game()
{
    if(!check_rules()){
        _model->getTimer()->setInterval(_view->get_Btime()->value() * g_second);
        _model->getTimer()->start();
        lock_buttons();
    }else{
        _view->paintErrorBox("Rules", "Check rules!");
    }
}

void Controller::stop_game()
{
    _model->getTimer()->stop();
   unlock_buttons();
}

void Controller::update_field() const
{
    _view->get_Wfield()->update();
    _view->update();
}

void Controller::unlock_buttons() const
{
    _view->get_Bstart()->setEnabled(true);
    _view->get_Bclear()->setEnabled(true);
    _view->get_Bsave()->setEnabled(true);
    _view->get_Bload()->setEnabled(true);
}

bool Controller::check_rules() const
{
    int Amax = _view->get_Bmax_alive()->value();
    int Amin = _view->get_Bmin_alive()->value();

    int Dmax = _view->get_Bmax_dead()->value();
    int Dmin = _view->get_Bmin_dead()->value();

    return Amax < Amin || Dmax < Dmin;
}

void Controller::lock_buttons() const
{
    _view->get_Bstart()->setEnabled(false);
    _view->get_Bclear()->setEnabled(false);
    _view->get_Bsave()->setEnabled(false);
    _view->get_Bload()->setEnabled(false);
    return;
}

void Controller::changeX(int const& x ){
    _model->set_size(x, _model->getHeight());
    update_field();
}


void Controller::changeY(int const&  y ){
    _model->set_size(_model->getWidth(), y);
    update_field();
}

void Controller::clear_field()
{
    _model->clear();
    update_field();
}

void Controller::generate()
{
   try{
        _model->new_Generation();
        update_field();
    }
    catch(const std::exception &e){
        _view->paintErrorBox("You Lost", e.what());
        stop_game();
        _view->update();
        return;
    }
}

void Controller::save_game()
{
    QString filename = (QFileDialog::getSaveFileName(_view,
                                                        tr("Save current game"),
                                                        QDir::homePath(),
                                                        tr("GameofLife *.LIFE Files (*.LIFE)")));

    if(filename.length() < 1)
            return;
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
        return;
    QString format = "#Life 1.06";
    QString rule = "#R ";
    QString Slife = format + "\n" + rule +
            _model->Sget_dead_rule()+ "/" +
            _model->Sget_alive_rule()  + "\n";

    file.write(Slife.toUtf8());
    file.write(_model->save_field().toUtf8());
    file.close();
}


void Controller::load_game()
{
    Parser pars_file(_model);
    QString filename = QFileDialog::getOpenFileName(_view,
                                                        tr("Open saved game"),
                                                        QDir::homePath(),
                                                        tr("Conway's Game Of Life File (*.LIFE)"));
    if(filename.length() < 1)
        return;
    QFile file(filename);
    QTextStream in(&file);
    if(!file.open(QIODevice::ReadOnly))
            return;
    if(!pars_file.is_life_format(in)){
        _view->paintErrorBox("Game format",
                             "It doesnt LIFE 1.06 format");
        return;
    }

    try{
        pars_file.store_params(in);
    }catch(const std::invalid_argument& error){
         _view->paintErrorBox("Game format", error.what());
         return;
    }
    _view->get_Bwidth()->setValue(_model->getWidth());
    _view->get_Bheight()->setValue(_model->getHeight());
    _view->update_rules_boxes();
    update_field();
    file.close();
}

void Controller::change_time(const double &value)
{
    _model->getTimer()->setInterval(value*g_second);
    update_field();
}

void Controller::change_alive_rule()
{
    int min = _view->get_Bmin_alive()->value();
    int max = _view->get_Bmax_alive()->value();

    _model->get_Valive().clear();
    for(int i = min ; i <= max ; i++){
        _model->get_Valive().push_back(i);
    }
    return;
}

void Controller::change_dead_rule()
{
    int min = _view->get_Bmin_dead()->value();
    int max = _view->get_Bmax_dead()->value();

    _model->get_Vdead().clear();
    for(int i = min ; i <= max ; i++){
        _model->get_Vdead().push_back(i);
    }
    return;
}



