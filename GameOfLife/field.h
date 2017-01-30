#ifndef FIELD_H
#define FIELD_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QMessageBox>
#include <memory>

#include "lifemodel.h"

class Field final: public QWidget
{
    Q_OBJECT
public:
    explicit Field(QWidget *parent = nullptr, Model* model = nullptr);
    ~Field();
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);

private slots:
    void paint_rects(QPainter* p);
    void paint_field(QPainter* p);

private:
    Model* _model = nullptr;
};

#endif // FIELD_H
