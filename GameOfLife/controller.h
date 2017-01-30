#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QMouseEvent>
#include <QFileDialog>
#include <QTextStream>
#include <memory>

#include "lifemodel.h"
#include "view.h"

class Controller final : public QObject
{
    Q_OBJECT
public:
    explicit Controller(Model* model = nullptr, View* view = nullptr);
    ~Controller();

public slots:
    void generate();
    void changeX(const int& x);
    void changeY(const int& y);
    void start_game();
    void stop_game();
    void clear_field();
    void save_game();
    void load_game();
    void change_time(const double& value);
    void change_alive_rule();
    void change_dead_rule();
private:
    Model* _model = nullptr;
    View* _view = nullptr;

    void update_field() const;
    void lock_buttons() const;
    void unlock_buttons() const;
    bool check_rules() const;
 };

#endif // CONTROLLER_H
