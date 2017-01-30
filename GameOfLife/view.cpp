#include "view.h"

View::View(Model* model) :
    ui(new Ui::MainWindow),
    Fgame(new Field(this,model)),
    _model(model)
{
    ui->setupUi(this);
    ui->field->addWidget(Fgame.get());
}

View::~View(){}

void View::update_rules_boxes()
{
    int alive_size = _model->get_Valive().size();
    int dead_size = _model->get_Vdead().size();
    ui->min_alive->setValue(_model->get_Valive()[0]);
    ui->min_dead->setValue(_model->get_Vdead()[0]);
    ui->max_alive->setValue(_model->get_Valive()[alive_size - 1]);
    ui->max_dead->setValue(_model->get_Vdead()[dead_size - 1]);

    update();
}

void View::paintErrorBox(const std::string& box_name, const std::string& error_name )
{
    QMessageBox::information(this,
                            tr(box_name.c_str()),
                            tr(error_name.c_str()),
                            QMessageBox::Ok);
}


