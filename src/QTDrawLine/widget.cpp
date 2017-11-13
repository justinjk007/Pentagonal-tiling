#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QPaintEvent>

class dataParts
{
 std::vector<QPoint> points;
};

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

// need to convert Point or Point_2 objects to QPoint objects
void setupDrawingParameters(const vector<Point> &c)
{
    points.resize(c.size());
    std::transform( std::begin(c), std::end(c), std::begin(points), [](K::Point_2 point)
    {
      return {point.x, point.y};
    });
}

//QPoint p1(10,10);
//QPoint p2(50,50);
//int pointCount = 3;
//QPoint points[3] =
//{
//      QPoint(10.0, 80.0),
//      QPoint(20.0, 10.0),
//      QPoint(80.0, 30.0),
//};

void Widget::paintEvent(QPaintEvent *e) {
    QPainter p(this);
    //p.fillRect(e->rect(), Qt::magenta);
    //p.drawLine(QPoint{10,10}, QPoint{50,50});
    //p.drawLine(p1,p2);
    //p.drawPolyline(points, pointCount);
    p.drawPolyline(points.data(), points.size());
}
