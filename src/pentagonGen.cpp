#include "pentagonGen.hpp"
#include <QPaintEvent>
#include <QPainter>

pentagonGen::pentagonGen(QWidget* parent) : QWidget(parent)
{
    // This is just some fake work so that the widget appears on the
    // start, it has something to draw
    Line line(Point(0, 0), Point(0, 0));
    this->current_pentagon.push_back(line);
    this->pixel_scaling = 0;
}

void pentagonGen::paintEvent(QPaintEvent* e)
{
    QPolygon polygon;
    for (const auto& line : this->current_pentagon) {
        polygon << QPoint(line.source.x, line.source.y);
    }
    // Make custom pen
    QPen pen;
    pen.setWidth(this->pixel_scaling);
    pen.setColor(QColor(42, 161, 152));
    // Make a brush to fill the polygon
    QBrush fill;
    fill.setColor(QColor(148, 208, 203));
    fill.setStyle(Qt::SolidPattern);
    QPainterPath canvas;
    QPainter painter(this);
    // painter.fillRect(e->rect(), QColor(238, 232, 213));  // Background color
    painter.setRenderHint(QPainter::Antialiasing);
    // Find the center and add the offset to get a good poistion before draw;
    int offestX = -60;
    int offestY = -100;
    QPoint painter_offest =
        QPoint(e->rect().center().x() + offestX, e->rect().center().y() + offestY);
    painter.translate(painter_offest);
    painter.setPen(pen);
    canvas.addPolygon(polygon);
    painter.drawPolygon(polygon);
    painter.fillPath(canvas, fill);
}

void pentagonGen::updateLine(std::vector<Line> pentagon)
{
    /**
     * Update the current line so it can drawn on to the widget
     */
    this->pixel_scaling    = 5;
    this->current_pentagon = pentagon;
    this->update();  // This function is inherited from Qt and it
                     // repaints the widget automatically
}
