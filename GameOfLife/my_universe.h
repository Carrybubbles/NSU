#ifndef MY_UNIVERSE_H
#define MY_UNIVERSE_H

#include <QLabel>
class my_universe : public QLabel
{
    Q_OBJECT
public:
    my_universe();
    int x;
    int y;
    void mousePressEvent(QMouseEvent *ev);
    void leaveEvent(QEvent *);

signals:
    void Mouse_Pressed();
    void mouse_pos();
    void Mouse_Left();
};

#endif // MY_UNIVERSE_H
