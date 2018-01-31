#include "pentagonGen.hpp"
#include <QPaintEvent>
#include <QPainter>

pentagonGen::pentagonGen(QWidget* parent) : QWidget(parent)
{
    this->current_line.source = Point(10.0, 80.0);
    this->current_line.target = Point(90.0, 20.0);
}

void pentagonGen::paintEvent(QPaintEvent* e)
{
    // Make custom pen
    QPen pen;
    pen.setWidth(3);
    pen.setColor(QColor(42, 161, 152));

    // Make the line and/or lines
    QLineF line(this->current_line.source.x, this->current_line.source.y,
                this->current_line.target.x, this->current_line.target.y);
    // Now draw the line to widget
    QPainter painter(this);
    painter.fillRect(e->rect(), QColor(238, 232, 213));  // Background color
    painter.setPen(pen);
    painter.drawLine(line);
}

void pentagonGen::updateLine(std::vector<Line> pentagon)
{
    /**
     * Update the current line so it can drawn on to the widget
     */
    for (auto& line : pentagon) {
        this->current_line.source = Point(line.source.x, line.source.y);
        this->current_line.target = Point(line.target.x, line.target.y);
        this->update();
    }
}
