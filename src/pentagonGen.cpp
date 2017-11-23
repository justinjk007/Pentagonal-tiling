#include "pentagonGen.hpp"
#include <QPaintEvent>
#include <QPainter>

pentagonGen::pentagonGen(QWidget* parent) : QWidget(parent)
{
    ;
}

void pentagonGen::paintEvent(QPaintEvent* e)
{
    // Make custom pen
    QPen pen;
    pen.setWidth(3);
    pen.setColor(QColor(42, 161, 152));

    // Make the line and/or lines
    QLineF line(10.0, 80.0, 90.0, 20.0);

    // Now draw the line to widget
    QPainter painter(this);
    painter.fillRect(e->rect(), QColor(238, 232, 213));  // Background color
    painter.setPen(pen);
    painter.drawLine(line);
}
