#include "tilingGen.hpp"
#include <QPaintEvent>
#include <QPainter>

tilingGen::tilingGen(QWidget* parent) : QWidget(parent)
{
    ;
}

void tilingGen::paintEvent(QPaintEvent* e)
{
    // Make custom pen
    QPen pen;
    pen.setWidthF(0.3); // Set width with floating point precision
    pen.setColor(QColor(42, 161, 152));

    // make a brush to fill the polygon
    QBrush fill;
    fill.setColor(QColor(148, 208, 203));
    fill.setStyle(Qt::SolidPattern);

    // Make the polygon
    QPolygon polygon;
    polygon << QPoint(1.5, 1.4);
    polygon << QPoint(4.8, 0.1);
    polygon << QPoint(7, 2.8);
    polygon << QPoint(5.1, 5.8);
    polygon << QPoint(1.7, 4.9);

    // Draw the polygon
    QPainterPath canvas;
    QPainter painter(this);
    painter.fillRect(e->rect(), QColor(238, 232, 213));
    painter.setPen(pen);
    canvas.addPolygon(polygon);
    painter.translate(50, 50);
    painter.scale(20, 20);
    painter.drawPolygon(polygon);
    painter.fillPath(canvas, fill);
}
