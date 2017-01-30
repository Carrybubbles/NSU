#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QTextStream>
#include <QStringList>
#include <QPushButton>
#include <QSpinBox>
#include <memory>

#include "field.h"
#include "lifemodel.h"
#include "ui_mainwindow.h"

namespace Ui {
class MainWindow;
}

class View final : public QMainWindow
{
    Q_OBJECT
public:
    explicit View(Model* model = nullptr);
    ~View();
    inline QPushButton *get_Bstart() const {return ui->start;}
    inline QPushButton *get_Bstop() const {return ui->stop;}
    inline QPushButton *get_Bclear() const {return ui->Clear;}
    inline Field *get_Wfield() const {return Fgame.get();}
    inline QSpinBox *get_Bwidth() const {return ui->width;}
    inline QSpinBox *get_Bheight() const{return ui->heigth;}
    inline QPushButton *get_Bload() const {return ui->Bload;}
    inline QPushButton *get_Bsave() const {return ui->Bsave;}
    inline QDoubleSpinBox *get_Btime() const {return ui->TimeChanger;}
    inline QSpinBox* get_Bmin_alive() const {return ui->min_alive;}
    inline QSpinBox* get_Bmax_alive() const {return ui->max_alive;}
    inline QSpinBox* get_Bmin_dead() const {return ui->min_dead;}
    inline QSpinBox* get_Bmax_dead() const {return ui->max_dead;}
    void update_rules_boxes();
    void paintErrorBox(const std::string& box_name, const std::string& error_name );
private:

    std::unique_ptr<Ui::MainWindow> ui;
    std::unique_ptr<Field> Fgame = nullptr;
    Model* _model = nullptr;
};

#endif // VIEW_H
