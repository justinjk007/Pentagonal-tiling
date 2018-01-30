#ifndef PENTAGONGEN_HPP
#define PENTAGONGEN_HPP

#include <QWidget>
#include "myGeometry.hpp"

class pentagonGen : public QWidget
{
    Q_OBJECT

   public:
    explicit pentagonGen(QWidget* parent = 0);
    void updateLine(Line);

   private:
    Line current_line;

   protected:
    void paintEvent(QPaintEvent* e) override;
};

#endif /* PENTAGONGEN_HPP */
