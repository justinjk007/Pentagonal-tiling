#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <vector>
//#include "../boundaryDetection.hpp"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void paintEvent(QPaintEvent* e) override;

    void updateVector (QVector<QPoint> &pointList);

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
