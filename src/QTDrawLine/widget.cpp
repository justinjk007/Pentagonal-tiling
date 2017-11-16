#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QPaintEvent>
#include <QVector>

static QVector<QPoint> points;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void updateVector (QVector<QPoint> &pointList)
{
    points = pointList;
    // not sure if we need to call update() here.

}

void Widget::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    p.drawPolyline(points.data(), points.size());
}
