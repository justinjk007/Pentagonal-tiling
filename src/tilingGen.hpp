#ifndef TILINGGEN_HPP
#define TILINGGEN_HPP

#include <QWidget>
#include <list>
#include "myGeometry.hpp"

class tilingGen : public QWidget
{
    Q_OBJECT

   public:
    explicit tilingGen(QWidget* parent = 0);
    void updateTiling(std::list<Line>);

   private:
    std::list<Line> current_tiling;

   protected:
    void paintEvent(QPaintEvent* e) override;
};

#endif /* TILINGGEN_HPP */
