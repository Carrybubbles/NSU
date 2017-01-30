#include "field.h"

Field::Field(QWidget *parent, Model* model):QWidget(parent),
    _model(model) {}

Field::~Field(){}

void Field::paintEvent(QPaintEvent *)
{
   QPainter p(this);
   paint_rects(&p);
   paint_field(&p);
}

void Field::paint_rects(QPainter* p)
{
    qreal CellWidth = static_cast<qreal>(width()) / _model->getWidth();
    qreal CellHeight = static_cast<qreal>(height()) / _model->getHeight();

    for(int i=0; i < _model->getHeight(); i++) {
        for(int j=0; j < _model->getWidth(); j++) {
            if(_model->getCell(j,i)== true) {
                qreal left = (static_cast<qreal>(CellWidth*j));
                qreal top  = (static_cast<qreal>(CellHeight*i));

                QRectF r(left, top, static_cast<qreal>(CellWidth),
                         static_cast<qreal>(CellHeight));

                p->fillRect(r, QBrush(Qt::red));
            }
        }
    }
}

void Field::paint_field(QPainter* p)
{
    qreal CellWidth = static_cast<qreal>(width()) / _model->getWidth() ;
    qreal CellHeight = static_cast<qreal>(height()) / _model->getHeight();
    QRect borders(0, 0 ,width() -1 ,height() - 1);
    for(qreal i = 0; i <= width(); i += CellWidth)
        p->drawLine(i, 0, i, height());

    for(qreal i = 0; i <= height(); i += CellHeight)
        p->drawLine(0, i, width(), i);
    p->drawRect(borders);
}

void Field::mousePressEvent(QMouseEvent *e){

    qreal CellWidth = static_cast<qreal>(width()) / _model->getWidth();
    qreal CellHeight = static_cast<qreal>(height()) / _model->getHeight();

    int i = floor(e->y()/CellHeight);
    int j = floor(e->x()/CellWidth);

    if(Qt::LeftButton == e->button()){
        _model->setCell(j,i);
    }else if(Qt::RightButton == e->button()){
        _model->deleteCell(j,i);
    }

    update();
}
void Field::mouseMoveEvent(QMouseEvent *e)
{
    qreal CellWidth = static_cast<qreal>(width()) / _model->getWidth();
    qreal CellHeight = static_cast<qreal>(height()) / _model->getHeight();

    int i = floor(e->y() / CellHeight);
    int j = floor(e->x() / CellWidth);

    if(_model->check_pos(j, i)){
        if(Qt::LeftButton & e->buttons()){
            _model->setCell(j,i);
            update();
       }else if(Qt::RightButton & e->buttons()){
            _model->deleteCell(j,i);
            update();
        }
    }
}
