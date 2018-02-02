#include "tilingGen.hpp"
#include <QPaintEvent>
#include <QPainter>

tilingGen::tilingGen(QWidget* parent) : QWidget(parent)
{
    // This is just some fake work so that the widget appears on the
    // start, it has something to draw
    Line line(Point(0, 0), Point(0, 0));
    this->current_tiling.push_back(line);
    this->current_tiling.push_back(line);
    this->current_tiling.push_back(line);
    this->current_tiling.push_back(line);
    this->current_tiling.push_back(line);
}

void tilingGen::paintEvent(QPaintEvent* e)
{
    // Make custom pen
    QPen pen;
    // pen.setWidthF(0.3);  // Set width with floating point precision
    pen.setWidth(7);
    pen.setColor(QColor(211, 54, 130));
    // Make a brush to fill the polygon
    QBrush fill;
    fill.setColor(QColor(148, 208, 203));
    fill.setStyle(Qt::SolidPattern);
    QPainterPath canvas;
    QPainter painter(this);
    // painter.fillRect(e->rect(), QColor(238, 232, 213));
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(pen);
    painter.translate(100, 100);
    painter.scale(0.6, 0.6);
    size_t count = 0;  // Count the number of points appended to the polygon
    QPolygon polygon;
    for (const auto& line : this->current_tiling) {
        polygon << QPoint(line.source.x, line.source.y);
        count++;
        if (count == 5) {
            // Draw the polygon
            canvas.addPolygon(polygon);
            painter.drawPolygon(polygon);
            painter.fillPath(canvas, fill);
            polygon.clear();  // Clear already painted data
            count = 0;        // Reset count
        }
    }
}

void tilingGen::updateTiling(std::list<Line> tiling)
{
    /**
     * Update the current tiling data so it can drawn on to the widget
     */
    this->current_tiling = tiling;
    this->update();  // This function is inherited from Qt and it
                     // repaints the widget automatically
}
